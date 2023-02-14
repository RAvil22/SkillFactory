#include "chat.h"

/*Методы класса PrivateChat*/
PrivateChat::PrivateChat(unsigned int chatID, unsigned int firstUserID, unsigned int secondUserID) : Chat(chatID, 2), firstUserID_{ firstUserID },
secondUserID_{ secondUserID } {
    //Проверка на существование вызываемого пользователя
    //Проверка на наличие текущего пользователя
    //unsigned int bannedUserID;
    //char c;
    //unsigned int size_;
    //Проверка на бан
    //Чтение ID
    //Чтение пароля
    //Чтение пользовательских настроек(Имя, размер подгрузки, видимость)
    //Чтение черного списка
    //Проверки на существование и бан вынести в приложение

    this->fileName_ = "Chat_" + to_string(this->chatID_) + ".txt";
    ifstream readFile(this->fileName_);
    if (!readFile.is_open()) {
        //Создать файл приватного чата
        ofstream fout(this->fileName_);
        if (fout.is_open()) {
            time_t curr{ time(nullptr)};
            fout.write((char*)&chatType_, sizeof(this->chatType_));
            fout.write((char*)&firstUserID_, sizeof(this->firstUserID_));
            fout.write((char*)&secondUserID_, sizeof(this->secondUserID_));
            fout.write((char*)&curr, sizeof(curr));
            fout.close();
        }
        else {throw NoOpen(this->fileName_);}
    }
    else {
        //Считать данные из файла приватного чата
        readFile.read((char*)&chatType_, sizeof(this->chatType_));
        readFile.read((char*)&firstUserID_, sizeof(this->firstUserID_));
        readFile.read((char*)&secondUserID_, sizeof(this->secondUserID_));
        time_t fileCurr;
        readFile.read((char*)&fileCurr, sizeof(fileCurr));
        this->lastUpdate_ = fileCurr;
        //Читать сообщения
        unsigned int id;
        time_t mesTime;
        unsigned int s;
        char c;
        string text;
        while (readFile.read((char*)&id, sizeof(id)) && readFile.read((char*)&mesTime, sizeof(mesTime))) {
            text = "";
            readFile.read((char*)&s, sizeof(s));
            for (unsigned int i{ 0 }; i < s; ++i) {
                readFile.read((char*)&c, sizeof(c));
                text += c;
            }
            this->messages_.push_back(shared_ptr<Message> (new Message(text, id, mesTime)));
        }
        readFile.close();
    }
}


bool PrivateChat::addMessage(shared_ptr<Message> mes) {
    //Обновление объекта чата
    this->lastUpdate_ = mes->getMessageSendTime();
    this->messages_.push_back(move(mes));
    //Создание указателя на последний элемент списка
    auto iter = messages_.end();
    --iter;
    //Проверка существования файла чата
    ifstream readFile(this->fileName_);
    if (readFile.is_open()) {
        unsigned int chatType;
        unsigned int firstID;
        unsigned int secondID;
        readFile.read((char*)&chatType, sizeof(chatType));
        readFile.read((char*)&firstID, sizeof(firstID));
        readFile.read((char*)&secondID, sizeof(secondID));
        readFile.close();
        //Проверка на отправителя
        if(firstID == (*iter)->getMessageSender() || secondID == (*iter)->getMessageSender());
        else return false;
        //Открытие файла в режиме чтения/записи
        fstream writeFile(this->fileName_, ios::in | ios::out);
        //Установка курсора в конец файла
        writeFile.seekp(0, ios::end);
        //Выделение памяти под lvalue ссылки
        unsigned int messSender{ (*iter)->getMessageSender() };
        time_t messTime{ (*iter)->getMessageSendTime() };
        //Запись содержимого lvalue ссылок в КОНЕЦ файла
        writeFile.write((char*)&messSender, sizeof(messSender));
        writeFile.write((char*)&messTime, sizeof(messTime));
        string temp{ (*iter)->getText() };
        unsigned int size_ = temp.size();
        writeFile.write((char*)&size_, sizeof(size_));
        char c;
        for (unsigned int i{ 0 }; i < size_; ++i) {
            c = temp[i];
            writeFile.write((char*)&c, sizeof(c));
        }
        //После записи содержимого сообщения, переход на позицию времени последнего изменения чата/
        writeFile.seekp(sizeof(unsigned int) + sizeof(unsigned int)+sizeof(unsigned int), ios::beg);
        //Запись нового значения времени последнего изменения чата/
        writeFile.write((char*)&messTime, sizeof(messTime));
        writeFile.close();
    }
    else {throw NoOpen(this->fileName_);}
}

bool PrivateChat::removeMessage(unsigned int num, unsigned int userID) {
    //Проверка на корректность
    if(num >= this->messages_.size() || num < 0){return false;}
    //Из сообщения с указанным номером взять время отправки сообщения и владельца сообщения
    auto iter{this->messages_.begin()};
    for(int i {0}; i < num; ++i){ //заменить на advance
        ++iter;
    }
    auto messSender{ (*iter)->getMessageSender()};
    auto messSendTime{ (*iter)->getMessageSendTime()};
    bool removeAllowed{false};
    //Проверка на владельца сообщения
    if(messSender == userID)removeAllowed = true;
    else return false;

    ifstream chatFile{this->fileName_};
    if(chatFile.is_open()){
        unsigned int chatType;
        unsigned int firstID;
        unsigned int secondID;
        time_t lastUpdate;

        chatFile.read((char*)&chatType, sizeof(chatType));
        chatFile.read((char*)&firstID, sizeof(firstID));
        chatFile.read((char*)&secondID, sizeof(secondID));
        chatFile.read((char*)&lastUpdate, sizeof(lastUpdate));

        unsigned int currSender;
        time_t currMessTime;
        unsigned int size_;
        char c;
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
                temp.push_back(shared_ptr<Message>(new Message(text, currSender, currMessTime)));
            }
        }
        chatFile.close();
        //Очистка файла до начала удаляемого сообщения
        ofstream chatFile(this->fileName_, ios::out);
        //Запись владельца, последнего изменения и имени чата
        chatFile.write((char*)&firstID, sizeof(firstID));
        chatFile.write((char*)&secondID, sizeof(secondID));
        chatFile.write((char*)&lastUpdate, sizeof(lastUpdate));

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

void PrivateChat::updateChatFromFile(shared_ptr<Message> mess) {
    ifstream readFile(this->fileName_);
    if (readFile.is_open()) {
        //Ключевые данные файла
        unsigned int chatType;
        unsigned int firstUserID;
        unsigned int secondUserID;
        time_t lastFileUpdate;
        //Время последнего прочтенного сообщения
        time_t messTime = mess->getMessageSendTime();
        //Переменные чтения/записи
        unsigned int id;
        time_t time;
        unsigned int s;
        char c;
        string text;
        //Получение информации о файле и его последнем изменении
        readFile.read((char*)&chatType, sizeof(chatType));
        readFile.read((char*)&firstUserID, sizeof(firstUserID));
        readFile.read((char*)&secondUserID, sizeof(secondUserID));
        readFile.read((char*)&lastFileUpdate, sizeof(lastFileUpdate));


        //Если промежуток между последним сообщением чата и временем указанном в mess(берется последнее сообщение чата у пользователя)
        //больше часа, обновить объект чата полностью
        if (lastFileUpdate - messTime > 3600) {
            this->messages_.clear();
            while (readFile.read((char*)&id, sizeof(unsigned int)) && readFile.read((char*)&time, sizeof(time_t))
                && readFile.read((char*)&s, sizeof(unsigned int))) {
                for (unsigned int i{ 0 }; i < s; ++i) {
                    readFile.read((char*)&c, sizeof(char));
                    text += c;
                }
                this->messages_.push_back(shared_ptr<Message>(new Message(text, id, time)));
            }
            readFile.close();
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
