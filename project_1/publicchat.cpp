#include "chat.h"

/*Методы класса PublicChat*/
PublicChat::PublicChat(const unsigned int chatID, const unsigned int chatOwnerID) : Chat(chatID, 1), chatOwnerID_{ chatOwnerID } {
    this->fileName_ = "Chat_" + to_string(this->chatID_) + ".txt";
    this->fileUsersName_ = "Chat_" + to_string(this->chatID_) + "_users.txt";
    ifstream readFile(this->fileName_);
    ifstream readUsersFile(this->fileUsersName_);
    if (readFile.is_open() && readUsersFile.is_open()) {
        readFile.close();
        readUsersFile.close();
        fillChatFromFiles();
    }
    else createChatFiles();
}

void PublicChat::createChatFiles(void){
    ofstream writeFile(this->fileName_, ios::out);
        if(writeFile.is_open()){
            //Занесение информации о типе чата
            writeFile.write((char*)&chatType_,sizeof(chatType_));
            //Занесение информации о владельце файла и его последнем изменении
            writeFile.write((char*)&chatOwnerID_, sizeof(chatOwnerID_));
            writeFile.write((char*)&lastUpdate_, sizeof(lastUpdate_));
            //Запись объекта чата в файлы
            char c;
            unsigned int size_;
            string text{this->chatName_};
            //Запись имени чата
            auto diff{128 - text.size()};
            if(diff){
                unsigned char plug = 127;
                for(int i{0}; i < diff; ++i)text += plug;
            }
            for(unsigned int i{0}; i < 128; ++i){
                c = text[i];
                writeFile.write((char*)&c, sizeof(c));
            }

            //Запись объектов сообщений в файл
            auto iter = this->messages_.begin();
            auto endList = this->messages_.end();
            while(iter != endList){
                shared_ptr<Message> mes = std::move(*iter) ;
                writeFile.write((char*)mes->getMessageSender(), sizeof(mes->getMessageSender()));
                writeFile.write((char*)mes->getMessageSendTime(), sizeof(mes->getMessageSendTime()));
                string temp{ mes->getText() };
                size_ = temp.size();
                char c;
                writeFile.write((char*)&size_, sizeof(size_));
                for (unsigned int i{ 0 }; i < size_; ++i) {
                    c = temp[i];
                    writeFile.write((char*)&c, sizeof(c));
                }
                ++iter;
            }
            writeFile.close();
        }
        else{throw NoOpen(this->fileName_);}

        ofstream usersWriteFile(this->fileUsersName_);
        if(usersWriteFile.is_open()){
            //usersWriteFile.write((char*)&chatOwnerID_, sizeof(chatOwnerID_));
            auto iter = this->userIDs_.begin();
            auto endList = this->userIDs_.end();
            while(iter != endList){
                    usersWriteFile.write((char*)&(*iter), sizeof(*iter));
                    ++iter;
            }
            usersWriteFile.close();
        }
        else{throw NoOpen(this->fileUsersName_);}
}

void PublicChat::fillChatFromFiles(void) {
    ifstream readFile(this->fileName_);
    ifstream readUsersFile(this->fileUsersName_);

    if(readUsersFile.is_open()){
        unsigned int chatUserID;
        while(readUsersFile.read((char*)&chatUserID, sizeof(chatUserID)))this->userIDs_.push_back(chatUserID);
        readUsersFile.close();
    }
    else{throw NoOpen(this->fileUsersName_);}

    if (readFile.is_open()) {
        unsigned int chatType;
        unsigned int chatFileOwnerID;
        time_t lastFileUpdate;
        char c;
        string text;

        //Получение информации о типе файла
        readFile.read((char*)&chatType,sizeof(chatType));
        this->chatType_ = chatType;

        //Получение информации о владельце файла, его последнем изменении и имени чата
        readFile.read((char*)&chatFileOwnerID, sizeof(chatFileOwnerID));
        readFile.read((char*)&lastFileUpdate, sizeof(lastFileUpdate));
        for(int i{0}; i < 128; ++i){
            readFile.read((char*)&c,sizeof(c));
            if(c!= 127)text += c;
        }
        this->chatOwnerID_ = chatFileOwnerID;
        this->lastUpdate_ = lastFileUpdate;
        this->chatName_ = text;
        text = "";

        //Копирование сообщений в список messages_
        unsigned int id;
        time_t mesTime;
        unsigned int s;
        while (readFile.read((char*)&id, sizeof(id)) && readFile.read((char*)&mesTime, sizeof(mesTime)) && readFile.read((char*)&s, sizeof(s))) {
            text = "";
            for (unsigned int i{ 0 }; i < s; ++i) {
                readFile.read((char*)&c, sizeof(c));
                text += c;
            }
            this->messages_.push_back(shared_ptr<Message>(new Message(text, id ,mesTime)));
        }

        readFile.close();
    }
    else{throw NoOpen(this->fileName_);}
}

bool PublicChat::addMessage(shared_ptr<Message> mes){
    //Обновление объекта чата
    this->lastUpdate_ = mes->getMessageSendTime();
    this->messages_.push_back(std::move(mes));
    //Создание указателя на последний элемент списка
    auto iter = messages_.end();
    --iter;
    //Проверка существования файла чата
    ifstream readFile(this->fileName_);
    if (readFile.is_open()) {
        readFile.close();
        //Открытие файла в режиме чтения/записи
        fstream writeFile(this->fileName_, ios::in | ios::out);
        //Установка курсора в конец файла
        writeFile.seekp(0,ios::end);
        //Выделение памяти под lvalue ссылки
        unsigned int messSender = (*iter)->getMessageSender();
        time_t messTime = (*iter)->getMessageSendTime();
        //Запись содержимого lvalue ссылок в КОНЕЦ файла
        writeFile.write((char*)&messSender, sizeof(messSender));
        writeFile.write((char*)&messTime, sizeof(messTime));
        string temp{ (*iter)->getText() };
        unsigned int size_ = temp.size();
        char c;
        writeFile.write((char*)&size_, sizeof(size_));
        for (unsigned int i{ 0 }; i < size_; ++i) {
            c = temp[i];
            writeFile.write((char*)&c, sizeof(c));
        }
        //После записи содержимого сообщения, переход на позицию времени последнего изменения чата
        writeFile.seekp(sizeof(unsigned int) + sizeof(unsigned int), ios::beg);
        //Запись нового значения времени последнего изменения чата
        writeFile.write((char*)&messTime, sizeof(messTime));
        writeFile.close();
        return true;
    }
    else {throw NoOpen(this->fileName_);}
}

bool PublicChat::removeMessage(unsigned int num, unsigned int userID) {
    //Проверка на корректность
    if(num >= this->messages_.size() || num < 0){return false;}
    //Из сообщения с указанным номером взять время отправки сообщения и владельца сообщения
    auto iter{this->messages_.begin()};
    for(int i {0}; i < num; ++i){
        ++iter;
    }
    auto messSender{(*iter)->getMessageSender()};
    auto messSendTime{(*iter)->getMessageSendTime()};
    bool removeAllowed{false};
    if(this->chatOwnerID_ == userID)removeAllowed = true;

    else{
        if(messSender == userID)removeAllowed = true;
        else return false;
    }

    if(removeAllowed){
        ifstream chatFile{this->fileName_};
        if(chatFile.is_open()){
            unsigned int chatType;
            unsigned int chatOwner;
            time_t lastUpdate;
            string chatName;
            char c;

            chatFile.read((char*)&chatType,sizeof(chatType));
            chatFile.read((char*)&chatOwner, sizeof(chatOwner));
            chatFile.read((char*)&lastUpdate, sizeof(lastUpdate));
            for(int i{0}; i < 128; ++i){
                chatFile.read((char*)&c, sizeof(c));
                chatName += c;
            }

            unsigned int currSender;
            time_t currMessTime;

            unsigned int size_;
            string text{""};

            list<shared_ptr<Message>> temp;
            //Найти сообщение
            while (chatFile.read((char*)&currSender, sizeof(currSender)) && chatFile.read((char*)&currMessTime, sizeof(currMessTime))
                   && chatFile.read((char*)&size_, sizeof(size_))) {
                text = "";
                for (unsigned int i{ 0 }; i < size_; ++i) {
                    chatFile.read((char*)&c, sizeof(c));
                    text += c;
                }
                if (currMessTime == messSendTime && currSender == messSender);
                else{
                    shared_ptr<Message> tempMess = make_shared<Message>(text, currSender, currMessTime );
                    temp.push_back(move(tempMess));
                }
            }
            chatFile.close();
            //Очистка файла до начала удаляемого сообщения
            ofstream chatFile(this->fileName_, ios::out);
            //Запись типа чата, владельца, последнего изменения и имени чата
            chatFile.write((char*)&chatType,sizeof(chatType));
            chatFile.write((char*)&chatOwner, sizeof(chatOwner));
            chatFile.write((char*)&lastUpdate, sizeof(lastUpdate));
            for(int i{0}; i < 128; ++i){
                chatFile.write((char*)&chatName[i], sizeof(chatName[0]));
            }
            auto tempIter = temp.begin();
            //Запись в файл скопированных сообщений
            while(tempIter != temp.end()){
                currSender = (*tempIter)->getMessageSender();
                currMessTime = (*tempIter)->getMessageSendTime();
                text = (*tempIter)->getText();
                size_ = text.size();
                chatFile.write((char*)&currSender, sizeof(currSender));
                chatFile.write((char*)&currMessTime, sizeof(currMessTime));
                chatFile.write((char*)&size_, sizeof(size_));
                for (auto i : text)chatFile.write((char*)&i, sizeof(i));
                ++tempIter;
            }
            chatFile.close();
            return true;
        }
        else{throw NoOpen(this->fileName_);}
    }
    else return false;
}

void PublicChat::updateChatFromFiles(shared_ptr<Message> mess) {
    ifstream readUsersFile(this->fileUsersName_);
    if(readUsersFile.is_open()){
        this->userIDs_.clear();
        unsigned int chatUserID;
        while(readUsersFile.read((char*)&chatUserID, sizeof(chatUserID)))this->userIDs_.push_back(chatUserID);
        readUsersFile.close();
    }
    else{throw NoOpen(this->fileUsersName_);}

    ifstream readFile(this->fileName_);
    if (readFile.is_open()) {
        //Ключевые данные файла
        unsigned int chatFileOwnerID;
        time_t lastFileUpdate;
        //Переменные чтения/записи
        unsigned int id;
        time_t time;
        unsigned int s;
        char c;
        string text;
        //Получение информации о файле и его последнем изменении
        readFile.read((char*)&chatFileOwnerID, sizeof(chatFileOwnerID));
        readFile.read((char*)&lastFileUpdate, sizeof(lastFileUpdate));
        time_t messTime;
        if(mess){messTime = mess->getMessageSendTime();}
        else{messTime = 0;}
        //Если промежуток между последним сообщением чата и временем указанном в mess(берется последнее сообщение чата у пользователя)
        //больше часа, обновить объект чата полностью
        if (lastFileUpdate - messTime > 3600) {
            this->messages_.clear();
            fillChatFromFiles();
            return;
        }

        if (lastFileUpdate > messTime) {
            while (readFile.read((char*)&id, sizeof(unsigned int)) && readFile.read((char*)&time, sizeof(time_t))
                && readFile.read((char*)&s, sizeof(unsigned int))) {
                for (unsigned int i{ 0 }; i < s; ++i) {
                    readFile.read((char*)&c, sizeof(char));
                    text += c;
                }
                if (time > messTime) {
                    this->messages_.push_back(shared_ptr<Message>(new Message(text, id, time)));
                }
            }
        }
        else readFile.close();
    }
    else{throw NoOpen(this->fileName_);}
}

void PublicChat::addUser(unsigned int userID){
    //Добавить в файл пользователей чата новый ID
    ofstream writeUsersFile(this->fileUsersName_, ios::app);
    if(writeUsersFile.is_open()){
        writeUsersFile.write((char*)userID, sizeof(userID));
        writeUsersFile.close();
    }
    else{throw NoOpen(this->fileUsersName_);}
}

void PublicChat::removeUser(unsigned int userID){
    //Изъять из файла чата указанный ID
    unsigned int id;
    list <unsigned int> ids;
    ifstream readUsersFile(this->fileUsersName_);
    if(readUsersFile.is_open()){
        while(readUsersFile.read((char*)&id,sizeof(id)))ids.push_back(id);
        auto iter{ids.begin()};
        auto end_{ids.end()};
        while(iter != end_){
            if(*iter == userID){
                ids.erase(iter);
                break;
            }
        }
        readUsersFile.close();
        ofstream writeUsersFile(this->fileUsersName_, ios::out);
        iter = ids.begin();
        end_ = ids.end();
        while(iter != end_)writeUsersFile.write((char*)&(*iter), sizeof(*iter));
        writeUsersFile.close();
    }
    else{throw NoOpen(this->fileUsersName_);}
}
