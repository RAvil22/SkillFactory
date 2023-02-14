#include "chat.h"

/*������ ������ PrivateChat*/
PrivateChat::PrivateChat(unsigned int chatID, unsigned int firstUserID, unsigned int secondUserID) : Chat(chatID, 2), firstUserID_{ firstUserID },
secondUserID_{ secondUserID } {
    //�������� �� ������������� ����������� ������������
    //�������� �� ������� �������� ������������
    //unsigned int bannedUserID;
    //char c;
    //unsigned int size_;
    //�������� �� ���
    //������ ID
    //������ ������
    //������ ���������������� ��������(���, ������ ���������, ���������)
    //������ ������� ������
    //�������� �� ������������� � ��� ������� � ����������

    this->fileName_ = "Chat_" + to_string(this->chatID_) + ".txt";
    ifstream readFile(this->fileName_);
    if (!readFile.is_open()) {
        //������� ���� ���������� ����
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
        //������� ������ �� ����� ���������� ����
        readFile.read((char*)&chatType_, sizeof(this->chatType_));
        readFile.read((char*)&firstUserID_, sizeof(this->firstUserID_));
        readFile.read((char*)&secondUserID_, sizeof(this->secondUserID_));
        time_t fileCurr;
        readFile.read((char*)&fileCurr, sizeof(fileCurr));
        this->lastUpdate_ = fileCurr;
        //������ ���������
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
    //���������� ������� ����
    this->lastUpdate_ = mes->getMessageSendTime();
    this->messages_.push_back(move(mes));
    //�������� ��������� �� ��������� ������� ������
    auto iter = messages_.end();
    --iter;
    //�������� ������������� ����� ����
    ifstream readFile(this->fileName_);
    if (readFile.is_open()) {
        unsigned int chatType;
        unsigned int firstID;
        unsigned int secondID;
        readFile.read((char*)&chatType, sizeof(chatType));
        readFile.read((char*)&firstID, sizeof(firstID));
        readFile.read((char*)&secondID, sizeof(secondID));
        readFile.close();
        //�������� �� �����������
        if(firstID == (*iter)->getMessageSender() || secondID == (*iter)->getMessageSender());
        else return false;
        //�������� ����� � ������ ������/������
        fstream writeFile(this->fileName_, ios::in | ios::out);
        //��������� ������� � ����� �����
        writeFile.seekp(0, ios::end);
        //��������� ������ ��� lvalue ������
        unsigned int messSender{ (*iter)->getMessageSender() };
        time_t messTime{ (*iter)->getMessageSendTime() };
        //������ ����������� lvalue ������ � ����� �����
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
        //����� ������ ����������� ���������, ������� �� ������� ������� ���������� ��������� ����/
        writeFile.seekp(sizeof(unsigned int) + sizeof(unsigned int)+sizeof(unsigned int), ios::beg);
        //������ ������ �������� ������� ���������� ��������� ����/
        writeFile.write((char*)&messTime, sizeof(messTime));
        writeFile.close();
    }
    else {throw NoOpen(this->fileName_);}
}

bool PrivateChat::removeMessage(unsigned int num, unsigned int userID) {
    //�������� �� ������������
    if(num >= this->messages_.size() || num < 0){return false;}
    //�� ��������� � ��������� ������� ����� ����� �������� ��������� � ��������� ���������
    auto iter{this->messages_.begin()};
    for(int i {0}; i < num; ++i){ //�������� �� advance
        ++iter;
    }
    auto messSender{ (*iter)->getMessageSender()};
    auto messSendTime{ (*iter)->getMessageSendTime()};
    bool removeAllowed{false};
    //�������� �� ��������� ���������
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
        //����� ���������
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
        //������� ����� �� ������ ���������� ���������
        ofstream chatFile(this->fileName_, ios::out);
        //������ ���������, ���������� ��������� � ����� ����
        chatFile.write((char*)&firstID, sizeof(firstID));
        chatFile.write((char*)&secondID, sizeof(secondID));
        chatFile.write((char*)&lastUpdate, sizeof(lastUpdate));

        auto tempIter = temp.begin();
        //������ � ���� ������������� ���������
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
        //�������� ������ �����
        unsigned int chatType;
        unsigned int firstUserID;
        unsigned int secondUserID;
        time_t lastFileUpdate;
        //����� ���������� ����������� ���������
        time_t messTime = mess->getMessageSendTime();
        //���������� ������/������
        unsigned int id;
        time_t time;
        unsigned int s;
        char c;
        string text;
        //��������� ���������� � ����� � ��� ��������� ���������
        readFile.read((char*)&chatType, sizeof(chatType));
        readFile.read((char*)&firstUserID, sizeof(firstUserID));
        readFile.read((char*)&secondUserID, sizeof(secondUserID));
        readFile.read((char*)&lastFileUpdate, sizeof(lastFileUpdate));


        //���� ���������� ����� ��������� ���������� ���� � �������� ��������� � mess(������� ��������� ��������� ���� � ������������)
        //������ ����, �������� ������ ���� ���������
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
