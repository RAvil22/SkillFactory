#include "main.h"


using namespace std;

int main(int argc, char** argv){

    /*struct UserIDs{
    unsigned int userID_;
    string userName_;
    };

    UserIDs first;
    UserIDs second;
    UserIDs third;
    UserIDs fourth;
    list<UserIDs> example;

    first.userID_ = 1;
    first.userName_ = "first";
    second.userID_ = 2;
    second.userName_ = "second";
    third.userID_ = 3;
    third.userName_ = "third";
    fourth.userID_ = 4;
    fourth.userName_ = "fourth";

    example.push_back(first);
    example.push_back(second);
    example.push_back(third);

    auto exIter = example.begin();
    fourth = *exIter;
    cout << fourth.userID_ << " " << fourth.userName_ << endl;
    ++exIter;
    cout << (*exIter).userID_ << " " << (*exIter).userName_ << endl;*/


    /*Message mes1("Hello",1);
    Message mes2("Goodbye", 2);
    PublicChat pc1(598, 1);
    pc1.sendMessage(mes1);
    pc1.sendMessage(mes2);
    cout << pc1.getChatID() << endl;
    cout << pc1.getMessageText(0) << endl;
    cout << pc1.getMessageText(1) << endl;
    cout << pc1.size() << endl;
    pc1.removeMessage(0);
    cout << pc1.size() << endl;
    pc1.setChatName("Public 1");
    cout << pc1.getChatName() << endl;*/

    User usa(14, "password", "usa");
    /*cout << usa.getNumberOfChats() << endl;
    usa.createPublicChat();
    usa.createPublicChat();
    usa.createPublicChat();
    usa.createPublicChat();
    usa.createPublicChat();
    usa.createPublicChat();
    usa.createPublicChat();
    usa.createPublicChat();
    usa.createPublicChat();
    usa.createPublicChat();
    cout << usa.getNumberOfChats() << endl;
    usa.removeOwnedChat(3);
    cout << usa.getNumberOfChats() << endl;
    usa.removeNonOwnedChat(1);
    cout << usa.getNumberOfChats() << endl;
    usa.showUserChatIDs();*/

    /*Message mess1{"first message\n\n\n\t joke", usa.getUserID()};*/
    Message mess2{"second 1", usa.getUserID()};
    /*Message mess3{"third 1", usa.getUserID()};
    Message mess4{"fourth 1", usa.getUserID()};
    Message mess5{"fifth 1", usa.getUserID()};
    Message mess6{"sixth 1", usa.getUserID()};

    Message mess7{"first message\n\n\n\t joke", usa.getUserID()};*/
    Message mess8{"second 2h", usa.getUserID()};
    /*Message mess9{"third 2", usa.getUserID()};
    Message mess10{"fourth 2", usa.getUserID()};
    Message mess11{"fifth 2", usa.getUserID()};
    Message mess12{"sixth 2", usa.getUserID()};

    unsigned int chatNum1{6};
    unsigned int chatNum2{8};

    usa.sendMessageToChat(mess1, chatNum1);
    usa.sendMessageToChat(mess2, chatNum1);

    usa.sendMessageToChat(mess7, chatNum2);
    usa.sendMessageToChat(mess8, chatNum2);*/



    int textLen1 = mess2.getText().length(); //Длина строки сообщения
    int textLen2 = mess8.getText().length(); //Длина строки сообщения

    /*cout << "Message 1 " << textLen1 << endl << mess2.getText() << endl << mess2.getMessageSender() << endl
    << mess2.getMessageSendTime() << endl << mess2.getMessageSendStatus() << endl;
    cout << "Message 2 " << textLen2 << endl << mess8.getText() << endl << mess8.getMessageSender() << endl
    << mess8.getMessageSendTime() << endl << mess8.getMessageSendStatus() << endl;*/

    string m1 = mess2.getText(); //Копия строки сообщения
    string m2 = mess8.getText(); //Копия строки сообщения
    unsigned int id1 = mess2.getMessageSender();
    unsigned int id2 = mess8.getMessageSender();
    time_t time1 = mess2.getMessageSendTime();
    time_t time2 = mess8.getMessageSendTime();
    bool stat1 = mess2.getMessageSendStatus();
    bool stat2 = mess8.getMessageSendStatus();

    const int m1_len{m1.length()};
    char m1_arr[m1_len];
    for(int i{0}; i < m1_len; ++i){m1_arr[i] = m1[i];}

    const int m2_len{m2.length()};
    char m2_arr[m2_len];
    for(int i{0}; i < m2_len; ++i){m2_arr[i] = m2[i];}


    /*Описание записи сообщения в файл НУЖНО*/
    ofstream testfile("test.txt", ios::out);

    testfile.write((char*)&id1, sizeof(unsigned int));
    testfile.write((char*)&time1, sizeof(time_t));
    testfile.write((char*)&stat1, sizeof(bool));
    testfile.write((char*)&textLen1, sizeof(int)); //Запись длины строки 1
    testfile.write((char*)&m1_arr, sizeof(m1_arr[0])*m1_len); //Запись строки 1 посимвольно

    testfile.write((char*)&id2, sizeof(unsigned int));
    testfile.write((char*)&time2, sizeof(time_t));
    testfile.write((char*)&stat2, sizeof(bool));
    testfile.write((char*)&textLen2, sizeof(int)); //Запись длины строки 2
    testfile.write((char*)&m2_arr, sizeof(m2_arr[0])*m2_len); //Запись строки 2 посимвольно

    testfile.close();

    /*Описание чтения сообщений из файла НУЖНО*/
    ifstream testfile_r("test.txt");
    if(testfile_r.is_open()){
        int len;
        char c;
        string text = "";
        unsigned int id;
        time_t time;
        bool stat;
        while(testfile_r.read((char*)&id,sizeof(unsigned int)) && testfile_r.read((char*)&time,sizeof(time_t)) &&
              testfile_r.read((char*)&stat,sizeof(bool)) && testfile_r.read((char*)&len, sizeof(int))){
            for(int i{0}; i < len; ++i){
                testfile_r.read((char*)&c, sizeof(char));
                text += c;
            }
            cout << "Read" << endl;
            cout << len << endl << text << endl << id << endl << time << endl << stat << endl << endl;
            text = "";
        }
	testfile.close();
    }


    return 0;
}

