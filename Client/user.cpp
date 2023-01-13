#include "user.h"

using namespace std;

User::User(unsigned int id, string password) : userID_{id}, password_{password} {}


/*Создание/удаление чатов*/////////////////////////////////////////////////////////////
bool User::createPublicChat(void){
    //Обращение к серверу за свободным ID чата
    //UserChat.userChatID_ = this->userID_ + size(userChats_);
    //UserChat temp(userChatID_ = this->userID_ + size(this->userChats_), userChat{this->userID_ + size(this->userChats_, this->userID_ );
    UserChat temp(this->getUserID(), getNumberOfChats());
    this->userChats_.push_back(temp);
    //Вставить сортировку списка по ChatID
    return true;
}

bool User::removeOwnedChat(const unsigned int chatID){
    // Найти чат в списке пользовательских чатов
    // Проверить пользователя на владение чатом
    // Если пользователь владеет чатом, удалить чат
    auto iter = searchUserChat(chatID);
    if(iter != this->userChats_.end()){
       auto temp = *iter;
       if(temp.userChat.getPublicChatOwner() == this->userID_){
            //Отправка запроса серверу на удаление чата на всех устройствах
            this->userChats_.erase(iter);
            return true;
       }
    }
    return false;
}

bool User::removeNonOwnedChat(const unsigned int chatID){
    auto iter = searchUserChat(chatID);
    if(iter != this->userChats_.end()){
        this->userChats_.erase(iter);
        return true;
    }
    else{return false;}
}


/*Поиск чата*/////////////////////////////////////////////////////////////
list<UserChat>::iterator User::searchUserChat(const unsigned int chatID){
    auto iter = this->userChats_.begin();
    while(iter != this->userChats_.end()){
        auto temp = *iter;
        if(temp.chatID_ == chatID){
            return iter;
        }
        ++iter;
    }
    return iter;
}

unsigned int User::searchChatID(const unsigned int chatID){ //Возврат ID чата
    //Проверить на наличие чата в профиле пользователя (searchUserChat)
    //Отправить запрос на сервер
    //Вернуть ответ сервера
}

list<string> User::searchChatName(const string){ //Возврат ID чатов подходящих чатов
    //Проверить на наличие чата в профиле пользователя (searchUserChat)
    //Отправить запрос на сервер
    //Вернуть ответ сервера
}

/*Подключение/покидание чатов*/////////////////////////////////////////////////////////////
bool User::joinToChat(unsigned int chatID){
    //Найти чат с ID chatID
    //Подать запрос на присоединение
    //При отрицательном ответе, вернуть false
    //При положительном ответе, добавить в список userChats структуру userChat c ID чата и копией showXMessages последних сообщений
    //Вернуть true
}

bool User::leaveChat(const unsigned int chatID){
    //Проверить на наличие чата в профиле пользователя (searchUserChat)
    //Если его нет, вернуть false
    //Если есть, и пользователь владелец чата, вызвать removeOwnedChat, вернуть true
    //Если есть, и пользователь не владелец чата, отправить серверу запрос на удаление
    //Если сервер не дает добро, вернуть false
    //Если сервер дает добро, вызвать removeNonOwnedChat, вернуть true
}

bool User::inviteToChat(const unsigned int chatID, const unsigned int userID){
    //Проверить на наличие пользователя с указанным ID(отправить запрос на сервер)
    //Если такого нет, или не принимает приглашения вернуть false
    //Если такой есть, направить запрос-приглашение на сервер
}

bool User::receiveToChat(const unsigned int chatID, const unsigned int userID){
    //Проверить на наличие пользователя с указанным ID(отправить запрос на сервер)
    //Если такого нет, вернуть false
    //Если такой есть, направить серверу запрос-прием в чат (Сервер должен добавить ID приглашаемого пользователя к контейнеру userIDs_)
    //return true
}

bool User::sendMessageToChat(Message message, unsigned int chatID){
    ///Найти нужный пользовательский чат
    auto iter = searchUserChat(chatID);

    if(iter != this->userChats_.end()){
        ///Если чат существует, добавить сообщение к списку
        iter->userChat.addMessage(message);
        ///Сформировать имя файла чата(Папка с файлами чата создана при присоединении)
        string fileaddr;
        time_t timepoint = time(nullptr);
        auto time = ctime(&timepoint);
        string date;
        for(int i{0}; i < 24; ++i){
            if((i >= 4 && i <= 6) || (i >= 8 && i <= 9) || (i >= 20 && i <= 23))date += time[i];
        }
        fileaddr = to_string(this->getUserID()) + "_" + to_string(iter->userChat.getChatID()) + "_" + date + ".txt";
        //cout << fileaddr << endl;
        ifstream check(fileaddr);
        if(!check.is_open()){
            ofstream file(fileaddr, ios::out);
            file << "Time\t";
            file << time;
            file << "UserID\t";
            file << getUserID() << endl;
            file << "Message text\t";
            file << message.getText() << endl << endl;
            file.close();
        }
        else{
            check.close();
            ofstream file(fileaddr, ios::app);
            file << "Time\t";
            file << time;
            file << "UserID\t";
            file << getUserID() << endl;
            file << "Message text\t";
            file << message.getText() << endl << endl;
            file.close();
        }
        return true;
    }

    else{
        //cout << "False" << endl;
        return false;
    }
}

bool User::showLastChatMessages(unsigned int chatID, const unsigned int showNum){
    auto iter = searchUserChat(chatID);
    if(iter != this->userChats_.end() && showNum < INT_MAX){
        if(iter->userChat.size() >= showNum){
            for(int i{showNum-1}; i >= 0; --i){
                cout << iter->userChat.getMessageText(i) << endl;
            }
        }
        else{
            for(int i{iter->userChat.size()-1}; i >= 0; --i){
                cout << iter->userChat.getMessageText(i) << endl;
            }
        }
        return true;
    }
    else return false;
}

























