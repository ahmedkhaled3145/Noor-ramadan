 #include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <fstream>
#include <limits>

using namespace std;

struct user {
    string name;
    int userID;
    string password;
    string hint;
    int tasbeehGoal;
    int quranGoal;
    int rosary;
    float totalPages;
    int points;
    string nickname;
} users [150];

struct athkar {
    int  thikrID;
    string content;
    string category;
    int target;
} athkarlist [200];

struct doaa {
    int  doaaID;
    string content;
    string category;
} doaalist [200];

struct dailyProgress {
    bool prayersDone[5];
    float quran;
    int tasbeeh;
} progress [150][30];

struct calendarDay {
    int day;
    string prayers[5] = { " الفجر "," الظهر "," العصر ","المغرب","العشاء" };
    string times [5];
    string event;
    string note;
} ramadan [30];

int userCount = 0;
int thikrCount = 0;
int doaaCount = 0;


void menu (int id);
void showRandomHadith ();
void printHeader ();
void rankIndex (int rankIndex);
void signUp ();
bool signUpNameCheck ( string username );
int login ();
void dailyReport(int userIndex);
void updateCalenderDay (int id , string password , string name);
void showCalenderDay ();
void updatePrayers ( int userIndex );
void rosary ( int userRosary );
void showAthkar ();
void showDoaa ();
void addThikr ( int id , string password , string name );
void addDoaa ( int id , string password , string name );
void saveUserData ();
void loadUserData ();
void saveAthkar ();
void loadAthkar ();
void saveDoaa ();
void loadDoaa ();
void saveProgress ();
void loadProgress ();
void saveCalendar ();
void loadCalendar ();



int main () {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL, "ar_EG.UTF-8");
    srand(time(0));

    loadUserData();
    loadProgress();
    loadAthkar();
    loadDoaa();
    loadCalendar();

    printHeader();
    showRandomHadith();

    while (true) {
        int x, id;
        do {
            while (true) {
                cout << "press ( 1 ) to Sign up : " << endl;
                cout << "press ( 2 ) to Log in : " << endl;
                cout << "press ( 3 ) to Exit : " << endl;
                cout << "      :  ";
                cin >> x;
                cout << "----------------------------------------------------------\n";
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << " Invalid input ! Please enter a number. \n ";
                    cout << "----------------------------------------------------------\n";
                }
                else {
                    if (x >= 1 && x <= 3)
                        break;
                    else {
                        cout << " Invalid input ! Please enter a number (1 or 2 or 3). \n ";
                        cout << "----------------------------------------------------------\n";
                    }
                }
            }

            switch (x) {
                case 1:
                    signUp();
                    break;

                case 2:
                    id = login();
                    if (id < 0)
                       x = 1;
                    break;
            }
        } while (x==1);

        if (x==2)
            menu(id);

        else if (x==3)
            break;
    }

    saveUserData();
    saveProgress();
    saveAthkar();
    saveDoaa();
    saveCalendar();

    return 0;
}



void printHeader() {

    cout << endl;
    cout << "\t\t\t\t\t===========================================" << endl;
    cout << "\t\t\t\t           ❤️ WELCOME TO NOOR RAMADAN SYSTEM ❤️       " << endl;
    cout << "\t\t\t\t\t===========================================" << endl;
    cout << "\t\t\t\t\t              RAMADAN KAREEM           " << endl;
    cout << "\t\t\t\t\t===========================================" << endl;
}


void showRandomHadith() {

    string hadith[10] =
    {
        "  ( من صلى علي صلاة واحدة صلى الله عليه عشراً ) ",
        " ( قال رسول الله : من رغب عن سنتي فليس مني ) ",
        "  (أكبر الكبائر: الإشراك بالله، وعقوق الوالدين، وشهادة الزور ) ",
        "  (من يرد الله به خيرا يفقهه في الدين) ",
        "  ( ما من مسلم يدعو لأخيه بظهر الغيب إلا قال الملَك: ولك بمثل ) ",
        "  (إن الله يقول يوم القيامة: أين المتحابون بجلالي اليوم أظلهم في ظلي يوم لا ظل إلا ظلي ) ",
        "  ( من سلك طريقاً يلتمس فيه علماً سهَّل الله له به طريقاً إلى الجنة ) ",
        " ( المسلم من سلم المسلمون من لسانه ويده والمهاجر من هجر ما نهى الله عنه ) ",
        "  (المؤمن للمؤمن كالبنيان يشد بعضه بعضا ) ",
        "(من كذب علي متعمداً فليتبوأ مقعده من النار)"
    };
    string s = " قال رسول الله صلى الله عليه و سلم : ";

    int i = rand() % 10;
    cout << "\n \t\t\t\t\t\t     " << " حديث اليوم " << endl;
    cout << "\t\t\t\t\t\t     " << "============" << endl;
    cout << "\n\t\t\t\t\t\t" << s  << endl;
    cout << "\t\t\t\t" << hadith[i]  << endl << endl;
    cout << "\t\t\t ---------------------------------------------------------------------------\n" << endl;
}


bool signUpNameCheck ( string username ) {

    for (int i = 0; i < userCount; i++) {
        if (users[i].name == username ) {
            return false;
        }
    }
    return true;
}


void signUp() {

    cout << "\t\t =================" <<endl;
    cout << "\t\t      SIGN UP           " << endl;
    cout << "\t\t =================" <<endl;
    cout << endl;

    string username;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        cout << " Enter Your Name :  ";
        getline(cin, username);

        if (signUpNameCheck(username))
            break;

        cout << "❌ Username already exists! Try again.\n";
        cout << "------------------------------------------------------------\n";
    }
    users[userCount].name = username;

    cout << " Creat Your Password :  ";
    getline(cin ,users[userCount].password);

    cout << "Enter a Hint in case you forget the password : ";
    getline(cin ,users[userCount].hint);

    users[userCount].userID = userCount;

    while (true) {
        cout << " Enter Your Daily Tasbeeh Goal :  ";
        cin >> users[userCount].tasbeehGoal;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " Invalid input ! Please enter a number. \n ";
            cout << "----------------------------------------------------------\n";
        }
        else
            break;
    }

    while (true) {
        cout << " Enter Your Daily Quran Goal (Number of pages) :  ";
        cin >> users[userCount].quranGoal;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " Invalid input ! Please enter a number. \n ";
            cout << "----------------------------------------------------------\n";
        }
        else
            break;
    }

    cout << "------------------------------------------------------------\n";
    cout << "\t Account Created Successfuly. \n";
    cout << "------------------------------------------------------------\n" << endl << endl;
    userCount++;
}

int login() {

    cout << "\t\t ==================" <<endl;
    cout << "\t\t       LOG IN           " << endl;
    cout << "\t\t ==================" <<endl;
    cout << endl;

    int id;
    string username, pass;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    bool correct_Name = false;
    bool checkForget = false;

    while (correct_Name == false) {

        cout << " Enter Your Name : ";
        getline(cin, username);

        for (int i = 0; i < userCount; i++) {
            if ( users[i].name == username) {
                correct_Name = true;
                id = i;
                break;
            }
        }

       if (correct_Name == false) {
            cout << "\t " << "❌ Wrong Name !  Try again.\n";
            cout << "------------------------------------------------------------\n";
           int x;
           while (true) {

               cout << "Press (1) Try again\n";
               cout << "Press (2) Return to Main Menu\n";
               cout << "      :  ";
               cin >> x;
               cout << "------------------------------------------------------------\n";
               if (cin.fail()) {
                   cin.clear();
                   cin.ignore(numeric_limits<streamsize>::max(), '\n');
                   cout << " Invalid input ! Please enter a number. \n ";
                   cout << "-----------------------------------------------------------\n";
               }
               else {
                   if (x == 1 || x == 2)
                       break;
                   else{
                      cout << " Invalid input ! Please enter a number (1 or 2).\n";
                      cout << "----------------------------------------------------------\n";
                   }
               }
           }
           if (x == 1) {
               cout << "  \t 🔄 Restarting login...\n";
               cout << "------------------------------------------------------------\n";
               return login();
           }
           else if (x == 2) {
               return -1;
            }

       }
    }

    bool correct_Pass = false;
    while ( correct_Pass == false ) {

        if (checkForget) {

            cout << "    Your Hint for the password is :  [ " << users [ id ].hint << " ] " << endl;
            cout << "------------------------------------------------------------\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << " Enter Your Password : ";
        getline(cin, pass);

        if (users [ id ].password == pass) {
            correct_Pass = true;
            break;
        }

        else {
            cout << "\t " << "❌ Wrong Password !  Try again.\n";
            cout << "-----------------------------------------------------------\n";

            int y;
            while (true) {

                cout << "Press (1) Try again\n";
                cout << "Press (2) Forgot password\n";
                cout << "Press (3) Return to Main Menu\n";
                cout << "      :  ";
                cin >> y;
                cout << "------------------------------------------------------------\n";
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << " Invalid input ! Please enter a number. \n ";
                    cout << "-----------------------------------------------------------\n";
                }
                else {
                    if (y == 1 || y == 2 || y == 3)
                       break;
                    else {
                       cout << " Invalid input ! Please enter a number (1 or 2 or 3).\n";
                       cout << "----------------------------------------------------------\n";
                    }
                }
            }
            if (y == 1) {
                cout << "------------------------------------------------------------\n";
                cout << "\t 🔄 Restarting login...\n";
                 cout << "------------------------------------------------------------\n";
                 return login();
            }
            else if (y == 2) {

                checkForget =  true;
            }
            else if (y == 3) {
                 return -1;
            }
        }
    }

    cout <<"\t " << "Login Successful. ✅\n";
    cout << "------------------------------------------------------------\n";
    cout << endl;
    return id;

}

void updateCalenderDay(int id , string password , string name) {

    if (  (id != users[0].userID && password != users[0].password && name != users[0].name))  {
        cout << "\t Access denied. Only admin  can add thikr. \n \t If you are an admin, please log in with your account."<< endl;
        cout << "------------------------------------------------------------\n";
        return;
    }

    else {
        cout << "\t\t ============================" <<endl;
        cout << "\t\t    قائمة إضافة أوقات الصلاة" << endl;
        cout << "\t\t ============================" <<endl;
        cout << endl;

        int d;
        while (true) {
            cout << " Enter today's date of the Ramadan ( Enter an integer ( 1 - 30 ) ) : ";
            cin >> d;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "------------------------------------------------------------\n";
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << " Invalid input ! Please enter a number. \n ";
                cout << "-----------------------------------------------------------\n";
            }
            else {
                if (d >= 1 && d <= 30)
                    break;

                else {
                    cout << " Invalid input ! Please enter a number from 1 to 30. \n ";
                    cout << "-----------------------------------------------------------\n";
                }

            }
        }

        ramadan [d-1].day = d;
        cout << endl;

        for (int i = 0; i < 5; i++) {

            cout << "أدخل موعد صلاة" << ramadan [d-1].prayers[i] << ":";
            getline(cin, ramadan [d-1].times[i]);
            cout << "\t ------------------------- \n";
        }

        cout << endl;
        cout << "أدخل حدث اليوم (إن لم يوجد أدخل 0 ) : ";
        getline(cin, ramadan [d-1].event);

        cout << endl;
        cout << "أدخل ملاحظات اليوم (إن لم يوجد أدخل 0 ) : ";
        getline(cin, ramadan[d-1].note);
        cout << endl;
        cout << "------------------------------------------------------------\n";
        cout << "\t " << "تم إدخال أوقات صلاة اليوم بنجاح ✅ ." << endl;
        cout << "------------------------------------------------------------\n";
        cout << endl;
    }

}


void showCalenderDay() {

    cout << "\t\t ============================" <<endl;
    cout << "\t\t      قائمة تقويم رمضان       " << endl;
    cout << "\t\t ============================" <<endl;
    cout << endl;

    int choice;
    while (true) {
        cout << "   أضغط ( 1 ) لرؤية تقويم شهر رمضان كامل" << endl;
        cout << "أضغط ( 2 ) لرؤية تقويم يوم محدد من الشهر" << endl;
        cout << "      :  ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "------------------------------------------------------------\n";

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " Invalid input ! Please enter a number. \n ";
            cout << "-----------------------------------------------------------\n";
        }
        else
            if (choice == 1 || choice == 2)
                break;
    }

    if (choice == 1) {

        cout << "\t  ===================================\n";
        cout << "\t       " << " تقويم شهر رمضان المبارك "  << endl;
        cout << "\t  ===================================\n";
        cout << endl;
        cout << "\t --------------------------- \n";

        for (int i = 0; i < 30; i++) {

            cout << "\t\t  " <<  i+1 << " رمضان " << endl;
            cout << "\t --------------------------- \n";
            cout << endl;

            for (int j = 0; j < 5; j++) {
                cout << "\t    " << "الصلاة :" << "     " << ramadan [i].prayers[j] << endl;
                cout << "\t    " << "الوقت :" << "     " << ramadan [i].times[j] << endl;
                cout << endl;
            }
            cout << "\t --------------------------- \n";
            cout << endl;

            if (ramadan[i].event != "0") {
                cout << "\t  " << ramadan[i].event << endl;
            }
            cout << endl;
            if (ramadan[i].note != "0") {
                cout << "\t  " << ramadan[i].note << endl;
            }

            cout << " -----------------------------------------------------------\n";
            cout << "\t --------------------------- \n";
        };
    }

    if (choice == 2) {

        int d;
        while (true) {
            cout << " Enter today's date of the Ramadan ( Enter an integer ( 1 - 30 ) ) : ";
            cin >> d;
            cout << "------------------------------------------------------------\n";
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << " Invalid input ! Please enter a number. \n ";
                cout << "-----------------------------------------------------------\n";
            }
            else {
                if (d >= 1 && d <= 30)
                    break;

                else {
                    cout << " Invalid input ! Please enter a number from 1 to 30. \n ";
                    cout << "-----------------------------------------------------------\n";
                }
            }
        }

        cout << "\t ---------------------------- \n";
        cout << "\t       " << "تقويم يوم " << d << " رمضان " << endl;
        cout << "\t ---------------------------- \n";
        cout << endl;

        for (int j = 0; j < 5; j++) {
            cout << "\t    " << "الصلاة :" << "     " << ramadan [d-1].prayers[j] << endl;
            cout << "\t    " << "الوقت :" << "     " << ramadan [d-1].times[j] << endl;
            cout << endl;
        }

        cout << "\t ---------------------------- \n";
        cout << endl;

        if (ramadan[d-1].event != "0") {
            cout << "\t   " << ramadan[d-1].event << endl;
        }
        cout << endl;
        if (ramadan[d-1].note != "0") {
            cout << "\t " << ramadan[d-1].note << endl;
        }

        cout << "-------------------------------------------------------------------\n";
    }

}



void addDoaa ( int id , string password , string name) {

   if ( (id == users[0].userID) && (password == users[0].password) && (name == users[0].name) ) {

       cout << "\t\t ==============================" <<endl;
       cout << "\t\t       قائمة إضافة الأدعية           " << endl;
       cout << "\t\t ==============================" <<endl;
       cout << endl;

       string added_doaa, category;

       cout << " ادخل  نص الدعاء :  ";
       cin.ignore(numeric_limits<streamsize>::max(), '\n');
       getline(cin , added_doaa);

       cout << " ادخل  فئة الدعاء :  ";

       getline(cin , category);

       for (int i = 0; i<doaaCount; i++) {
           if (doaalist[i].content == added_doaa && category == doaalist[i].category) {
               cout << "\t " <<  "الدعاء موجود بالفعل !" << endl;
               cout << "------------------------------------------------------------\n";
               return;
           }
       }

       cout << " ادخل الرقم التعريفي للدعاء : ";
       cin >> doaalist[doaaCount].doaaID;

       doaalist[doaaCount].content =  added_doaa ;
       doaalist[doaaCount].category =  category;
       doaaCount++;

       cout << "\t " <<  " تم اضافة الدعاء  بنجاح ✅ ." << endl;
       cout << "------------------------------------------------------------\n";

   }
   else {
        cout << "\t Sorry, this is not the admin account."<< endl;
        cout << "\t You cannot select this option." << endl;
       cout << "------------------------------------------------------------\n";
   }

 }


void addThikr ( int id , string password , string name ) {

    if (  (id != users[0].userID && password != users[0].password && name != users[0].name))  {
        cout << "\t Access denied. Only admin  can add thikr. \n \t If you are an admin, please log in with your account."<< endl;
        cout << "------------------------------------------------------------\n";
        return;
    }

    else{

        cout << "\t\t ==============================" <<endl;
        cout << "\t\t       قائمة إضافة الأذكار           " << endl;
        cout << "\t\t ==============================" <<endl;
        cout << endl;

        string addThikr, category;

        cout << " ادخل نص الذكر  :  ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin ,  addThikr );

        cout << " ادخل فئة الذكر : ";
        getline(cin ,  category );

        for (int i = 0; i < thikrCount; i++) {
            if (athkarlist[i].content == addThikr && athkarlist[i].category == category) {
                cout << "\t " << "الذكر موجود بالفعل !" << endl;
                cout << "------------------------------------------------------------\n";
                return;
            }
        }

        cout << " ادخل  عدد تكرار الذكر : ";
        cin >> athkarlist[thikrCount].target ;

        cout << " ادخل الرقم التعريفي للذكر : ";
        cin >> athkarlist[thikrCount].thikrID;

        athkarlist[thikrCount].content = addThikr;
        athkarlist[thikrCount].category = category;
        thikrCount++;

        cout << "\t " <<  "تم إضافة الذكر بنجاح ✅ ." << endl;
        cout << "------------------------------------------------------------\n";

    }

}


void updatePrayers(int userIndex ) {

    cout << "\t\t ========================================" <<endl;
    cout << "\t\t       قائمة تحديث الصلوات و القرآن           " << endl;
    cout << "\t\t ========================================" <<endl;
    cout << endl;

    string prayers[5] = { " الفجر "," الظهر "," العصر "," المغرب "," العشاء " };

     int day;
    while (true) {
        cout << " Enter today's date of the Ramadan ( Enter an integer ( 1 - 30 ) ) : ";
        cin >> day;
        cout << "------------------------------------------------------------\n";
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " Invalid input ! Please enter a number. \n ";
            cout << "----------------------------------------------------------\n";
        }
        else {
            if (day >= 1 && day <= 30)
                break;
            else {
                cout << " Invalid input ! Please enter a number from 1 to 30. \n ";
                cout << "----------------------------------------------------------\n";
            }
        }
    }

    cout << "\t\t " <<  " اليوم " << day << " من رمضان "  << endl;

    cout << "----------------------------------------------------------\n";

    while (true) {
    cout << " كم صفحة من القران قرأت ؟ " << endl;
    cin >> progress[userIndex][day-1].quran;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << " Invalid input ! Please enter a number. \n ";
    }
    else
        break;
   }


    users[userIndex].points += (( progress[userIndex][day-1].quran ) * 2);
    users[userIndex].totalPages += progress[userIndex][day-1].quran;

    cout << "----------------------------------------------------------\n";
    if (progress[userIndex][day-1].quran < users[userIndex].quranGoal) {

        cout << " لم تحقق الهدف  " << "[ " <<  users[userIndex].quranGoal <<" / " << progress[userIndex][day-1].quran << " ]" << endl;
    }
    else
        cout << " حققت الهدف  " << "[ " <<  users[userIndex].quranGoal <<" / " << progress[userIndex][day-1].quran << " ] ✅" << endl;

    cout << "----------------------------------------------------------\n";
    cout << "\n press ( 1 ) for YES  and  ( 0 ) for NO.\n\n ";

    int i = 0;
    while (i < 5)
    {

        while (true)
        {
            cout << " هل صليت " << prayers[i] << "؟" << endl;
            cin >> progress[userIndex][day-1].prayersDone[i];

            if (cin.fail()) {
                cin.clear();
                cout << "press only 1 or 0 \n";
                continue;
            }
            if (progress[userIndex][day-1].prayersDone[i] == 1 || progress[userIndex][day-1].prayersDone[i] == 0)
                break;
        }

        i++;
    }
    cout << "----------------------------------------------------------\n";

    for (i = 0; i < 5; i++) {

        cout << "\t    " << "صلاة" << prayers[i] << ":";
        if (progress[userIndex][day-1].prayersDone[i] == 1) {
            cout << " \t    " << " تم ✅ " << endl;
            users[userIndex].points += 5;
        }

        else
            cout<<"     " << "لم يتم ❌"<< endl;
    }
    cout << "----------------------------------------------------------\n";
}


void rosary (int userRosary) {
    int count  , day , counter = 0;
    char key;

    while (true) {
        cout << " Enter today's date of the Ramadan ( Enter an integer ( 1 - 30 ) ) : ";
        cin >> day;
        cout << "------------------------------------------------------------\n";
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " Invalid input ! Please enter a number. \n ";
            cout << "----------------------------------------------------------\n";
        }
        else {
            if (day >= 1 && day <= 30)
                break;
            else {
                cout << " Invalid input ! Please enter a number from 1 to 30. \n ";
                cout << "----------------------------------------------------------\n";
            }
        }
    }

    count = users[userRosary].rosary;

    while (true) {

        while (true) {
            cout << "\t -------------------------------------------------" << endl;
            cout << "\t " << "                  السبحة الإلكترونية                  " << endl;
            cout << "\t -------------------------------------------------" << endl;
            cout << endl;
            cout << "\t\t\t    " <<   "العداد :    " << "[  " << count << "  ] "  <<  endl;
            cout << endl;
            cout << "\t -------------------------------------------------" << endl;
            cout << "\t   ( + ) -> Add ( تسبيح )            " << endl;
            cout << "\t   ( 0 ) -> Reset ( تصفير السبحة )             " << endl;
            cout << "\t   ( q ) -> Exit  ( خروج )                   " << endl;
            cout << "\t -------------------------------------------------" << endl;
            cout << endl << endl;

            cout << " Press  ( + ) or ( 0 ) or ( q ) : ";
            cin >> key;

            if (key == '+' || key == '0' || key == 'q' || key == 'Q')
                break;
        }

        if (key == '+') {
            count++;
            counter++;
            progress[userRosary][day-1].tasbeeh ++;
            cout << endl;
            cout << endl;
            cout << endl;
        }
        else if (key == '0') {
            count = 0;
            cout << endl;
            cout << endl;
            cout << endl;
        }

        else if (key == 'q' || key == 'Q') {
            cout << endl;
            break;
        }
    }

    cout << "----------------------------------------------------------\n";

    users[userRosary].rosary = count;
    users[userRosary].points += counter / 2;

}


void rankIndex (int rankIndex) {

    if (users[rankIndex].points <= 600)
        users[rankIndex].nickname = "مبتدئ";

    else if (users[rankIndex].points <= 1500)
        users[rankIndex].nickname = "مثابر";

    else
        users[rankIndex].nickname = "متدين";

}


void showAthkar() {

    int type;
    char check;
    do{

        while (true) {

            cout << "\t\t =========================" <<endl;
            cout << "\t\t       قائمة  الأذكار           " << endl;
            cout << "\t\t =========================" <<endl;
            cout << endl;

            while (true) {

                cout << "\t " << "      اضغط (1) لعرض أذكار الصباح"<<endl;
                cout << "\t " << "      اضغط (2) لعرض أذكار المساء" <<endl;
                cout << "\t " << "    اضغط (3) لعرض أذكار الإستيقاظ"<<endl;
                cout << "\t " << "       اضغط (4) لعرض أذكار النوم" <<endl;
                cout << "\t " << "اضغط (5) لعرض أذكار ما بعد الصلاة"<<endl;
                cout << "\t " << "                 اضغط (0) للخروج" <<endl;
                cout << "      :  ";
                cin >> type;
                cout << "------------------------------------------------------------\n";

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << " Invalid input ! Please enter a number. \n ";
                    cout << "----------------------------------------------------------\n";
                }
                else
                    break;
            }

            if (type >=0 && type <= 5) {
                break;
            }
        }

        switch (type) {

            case 1:

                cout << "\t   ---------------------------------" << endl;
                cout << "\t\t " << "     أذكار الصباح  " << endl;
                cout << "\t   ---------------------------------" << endl;
                cout << endl;
                for (int i = 0; i < thikrCount; i++) {
                    if (athkarlist[i].category == "الصباح" || athkarlist[i].thikrID == 1) {
                        cout << "    " << athkarlist[i].content<<endl;
                        cout << "\t" << "[ عدد مرات التكرار :  " << athkarlist[i].target<< " ] " <<endl;
                        cout << endl;
                        cout  << "\t\t" << "---------------" <<endl;
                    }
                }
                cout << "------------------------------------------------------------" << endl;
                cout << endl;
                break;

            case 2:

                cout << "\t   ---------------------------------" << endl;
                cout << "\t\t " << "     أذكار المساء  " << endl;
                cout << "\t   ---------------------------------" << endl;
                cout << endl;

                for (int i = 0; i < thikrCount; i++) {
                    if (athkarlist[i].category == "المساء" || athkarlist[i].thikrID == 2) {
                        cout << "    " << athkarlist[i].content<<endl;
                        cout << "\t" << "[ عدد مرات التكرار :  " << athkarlist[i].target<< " ] " <<endl;
                        cout << endl;
                        cout  << "\t\t" << "---------------" <<endl;
                    }
                }

                cout << "------------------------------------------------------------" << endl;
                cout << endl;
                break;

            case 3:

                cout << "\t   ---------------------------------" << endl;
                cout << "\t\t " << "    أذكار الإستيقاظ   " << endl;
                cout << "\t   ---------------------------------" << endl;
                cout << endl;

                for (int i = 0; i < thikrCount; i++) {
                    if (athkarlist[i].category == "الإستيقاظ" || athkarlist[i].thikrID == 3) {
                        cout << "    " << athkarlist[i].content<<endl;
                        cout << "\t" << "[ عدد مرات التكرار :  " << athkarlist[i].target<< " ] " <<endl;
                        cout << endl;
                        cout  << "\t\t" << "---------------" <<endl;
                    }
                }

                cout << "------------------------------------------------------------" << endl;
                cout << endl;
                break;

            case 4:

                cout << "\t   ---------------------------------" << endl;
                cout << "\t\t " << "     أذكار النوم  " << endl;
                cout << "\t   ---------------------------------" << endl;
                cout << endl;

                for (int i = 0; i < thikrCount; i++) {
                    if (athkarlist[i].category == "النوم" || athkarlist[i].thikrID == 4) {
                        cout << "    " << athkarlist[i].content<<endl;
                        cout << "\t" << "[ عدد مرات التكرار :  " << athkarlist[i].target<< " ] " <<endl;
                        cout << endl;
                        cout  << "\t\t" << "---------------" <<endl;
                    }
                }

                cout << "-----------------------------------------------------------" << endl;
                cout << endl;
                break;

            case 5:

                cout << "\t   ----------------------------------" << endl;
                cout << "\t\t " << "   أذكار ما بعد الصلاة" << endl;
                cout << "\t   ----------------------------------" << endl;
                cout << endl;
                for (int i = 0; i < thikrCount; i++) {
                    if (athkarlist[i].category ==  "الصلاة" || athkarlist[i].thikrID == 5) {
                        cout << "    " << athkarlist[i].content<<endl;
                        cout << "\t" << "[ عدد مرات التكرار :  " << athkarlist[i].target<< " ] " <<endl;
                        cout << endl;
                        cout  << "\t\t" << "---------------" <<endl;
                    }
                }
                cout << "------------------------------------------------------------" << endl;
                cout << endl;
                break;

            default:
                return;
        }
        cout <<"للرجوع لقائمة الأذكار أضغط ( y )"<< endl;
        cout << "      :  ";
        cin >> check;
        cout << "------------------------------------------------------------" << endl;

    } while (check == 'y' || check == 'Y');

}


void showDoaa() {

    int choice;
    char check;
    do {
        while (true) {

            cout << "\t\t =========================" <<endl;
            cout << "\t\t       قائمة  الأدعية           " << endl;
            cout << "\t\t =========================" <<endl;
            cout << endl;

            while (true) {

                cout << "\t " << "         اضغط (1)  لدعاء التوبة"<<endl;
                cout << "\t " << "    اضغط (2)  لدعاء طلب المغفرة" <<endl;
                cout << "\t " << "     اضغط (3)  لدعاء ليلة القدر"<<endl;
                cout << "\t " << "     اضغط (4)  لدعاء نزول المطر" <<endl;
                cout << "\t " << "     اضغط (5)  لدعاء طلب الشفاء" <<endl;
                cout << "\t " << "        اضغط (6)  لدعاء الهدايه" <<endl;
                cout << "\t " << "    اضغط (7)  لدعاء تفريج الكرب" <<endl;
                cout << "\t " << "اضغط (8)  لدعاء للأهل و المسلمين" <<endl;
                cout << "\t " << "  اضغط (9)  لدعاء الشكر و الحمد" <<endl;
                cout << "\t " << "                اضغط (0) للخروج " <<endl;
                cout << "      :  ";
                cin >> choice;
                cout << "------------------------------------------------------------\n";

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << " Invalid input ! Please enter a number. \n ";
                    cout << "----------------------------------------------------------\n";
                }
                else
                    break;
            }

            if ( choice >=0 && choice <= 9 )
                break;
        }

        int arrang = 1;

        switch (choice)
        {
            case 1:

                cout << "\t   ---------------------------------" << endl;
                cout << "\t\t " << "     أدعية التوبة  " << endl;
                cout << "\t   ---------------------------------" << endl;
                cout << endl;
                for (int i = 0; i < doaaCount; i++) {
                    if (doaalist[i].category == "التوبة" || doaalist[i].doaaID == 1) {
                        cout << "\t" << doaalist[i].content << "\t" << arrang << endl;
                        cout << endl;
                        cout  << "\t\t" << "---------------" <<endl;
                        arrang++;
                    }
                }

                cout << "------------------------------------------------------------" << endl;
                cout << endl;
                break;

            case 2:

                cout << "\t   ---------------------------------" << endl;
                cout << "\t\t " << "    أدعية المغفرة   " << endl;
                cout << "\t   ---------------------------------" << endl;
                cout << endl;
                for (int i = 0; i < doaaCount; i++) {
                    if (doaalist[i].category == "المغفرة" || doaalist[i].doaaID == 2) {
                        cout << "\t" << doaalist[i].content << "\t" << arrang<< endl;
                        cout << endl;
                        cout  << "\t\t" << "---------------" <<endl;
                        arrang++;
                    }
                }

                cout << "------------------------------------------------------------" << endl;
                cout << endl;
                break;

            case 3:

                cout << "\t   ---------------------------------" << endl;
                cout << "\t\t " << "  أدعية ليلة القدر    " << endl;
                cout << "\t   ---------------------------------" << endl;
                cout << endl;
                for (int i = 0; i < doaaCount; i++) {
                    if (doaalist[i].category == "ليلة القدر" || doaalist[i].doaaID == 3) {
                        cout << "\t" << doaalist[i].content << "\t" << arrang << endl;
                        cout << endl;
                        cout  << "\t\t" << "---------------" <<endl;
                        arrang++;
                    }
                }

                cout << "------------------------------------------------------------" << endl;
                cout << endl;
                break;

            case 4:

                cout << "\t   ---------------------------------" << endl;
                cout << "\t\t " << "     أدعية المطر  " << endl;
                cout << "\t   ---------------------------------" << endl;
                cout << endl;
                for (int i = 0; i < doaaCount; i++) {
                    if (doaalist[i].category == "المطر" || doaalist[i].doaaID == 4) {
                        cout << "\t" << doaalist[i].content << "\t" << arrang << endl;
                        cout << endl;
                        cout  << "\t\t" << "---------------" <<endl;
                        arrang++;
                    }
                }
                cout << "------------------------------------------------------------" << endl;
                cout << endl;
                break;

            case 5:

                cout << "\t   ---------------------------------" << endl;
                cout << "\t\t " << "  أدعية  شفاء المريض    " << endl;
                cout << "\t   ---------------------------------" << endl;
                cout << endl;
                for (int i = 0; i < doaaCount; i++) {
                    if (doaalist[i].category == "الشفاء" || doaalist[i].doaaID == 5) {
                        cout << "\t" << doaalist[i].content << "\t" << arrang << endl;
                        cout << endl;
                        cout  << "\t\t" << "---------------" <<endl;
                        arrang++;
                    }
                }

                cout << "------------------------------------------------------------" << endl;
                cout << endl;
                break;

            case 6:

                cout << "\t   ---------------------------------" << endl;
                cout << "\t\t " << "  أدعية الهداية    " << endl;
                cout << "\t   ---------------------------------" << endl;
               cout << endl;
                for (int i = 0; i < doaaCount; i++) {
                    if (doaalist[i].category == "الهدايه" || doaalist[i].doaaID == 6) {
                        cout << "\t" << doaalist[i].content << "\t" << arrang << endl;
                        cout << endl;
                        cout  << "\t\t" << "---------------" <<endl;
                        arrang++;
                    }
                }

                cout << "------------------------------------------------------------" << endl;
                cout << endl;
                break;

            case 7:

                cout << "\t   ---------------------------------" << endl;
                cout << "\t\t" << "  أدعية تفريج الكرب   " << endl;
                cout << "\t   ---------------------------------" << endl;
                cout << endl;
                for (int i = 0; i < doaaCount; i++) {
                    if (doaalist[i].category == "الكرب" || doaalist[i].doaaID == 7) {
                        cout << "\t" << doaalist[i].content << "\t" << arrang << endl;
                        cout << endl;
                        cout  << "\t\t" << "---------------" <<endl;
                        arrang++;
                    }
                }

                cout << "------------------------------------------------------------" << endl;
                cout << endl;
                break;

            case 8:

                cout << "\t   ---------------------------------" << endl;
                cout << "\t\t" << "أدعية للأهل و المسلمين  " << endl;
                cout << "\t   ---------------------------------" << endl;
                cout << endl;
                for (int i = 0; i < doaaCount; i++) {
                    if (doaalist[i].category == "للأهل و المسلمين" || doaalist[i].doaaID == 8) {
                        cout << "\t" << doaalist[i].content << "\t" << arrang << endl;
                        cout << endl;
                        cout  << "\t\t" << "---------------" <<endl;
                        arrang++;
                    }
                }

                cout << "------------------------------------------------------------" << endl;
                cout << endl;
                break;

            case 9:

                cout << "\t   ---------------------------------" << endl;
                cout << "\t\t" << "  أدعية الشكر و الحمد   " << endl;
                cout << "\t   ---------------------------------" << endl;
                cout << endl;
                for (int i = 0; i < doaaCount; i++) {
                    if (doaalist[i].category == "الشكر و الحمد" || doaalist[i].doaaID == 9) {
                        cout << "\t" << doaalist[i].content << "\t" << arrang << endl;
                        cout << endl;
                        cout  << "\t\t" << "---------------" <<endl;
                        arrang++;
                    }
                }

                cout << "------------------------------------------------------------" << endl;
                cout << endl;
                break;

            default:
                return;
        }

        cout <<"للرجوع لقائمة الأدعية أضغط ( y )"<< endl;
        cout << "      :  ";
        cin >> check;
        cout << "------------------------------------------------------------" << endl;
    } while (check == 'y' || check == 'Y');
}


void dailyReport(int userIndex) {
    rankIndex (userIndex);

    cout << "\t  ================================\n";
    cout << "\t     " << " قائمة الإنجازات اليومية  "<<endl;
    cout << "\t  ================================\n";
    cout << endl;

    int day;
    while (true) {
        cout << "Enter today's date of the month ( Enter an integer ) : ";
        cin >> day;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " Invalid input ! Please enter a number. \n ";
            cout << "------------------------------------------------------------" << endl;
        }
        else
            if (day >= 1 && day <= 30)
                break;
            else
                cout << " Invalid input ! Please enter a number from 1 to 30. \n ";
        cout << "------------------------------------------------------------" << endl;
    }
    cout << endl << endl;

    day--;

    cout << "\t" << "  الاسم        : " << "\t " << users[userIndex].name << endl;
    cout << "\t" << "  اللقب      : " << "\t " << users[userIndex].nickname << endl;
    cout << endl;
    cout << "\t ------------------------------------------ \n";
    cout << endl;
    cout  << "\t\t\t" << " [ القرآن  ]"<<endl;
    cout  << "\t\t\t" << "-------------" <<endl;
    cout << endl;
    cout << "\t" << "عدد الصفحات التي  قرأتها اليوم  : " << "\t" << progress[userIndex][day].quran << endl;
    cout << "\t" << " الهدف اليومي  :    " << "\t" << users[userIndex].quranGoal << endl;
    cout << endl;
    cout << "\t         ---------------------------- \n";

    if (progress[userIndex][day].quran < users[userIndex].quranGoal)
        cout << "\t     " << " لم تحقق الهدف  " << "[ " <<  users[userIndex].quranGoal <<" / " << progress[userIndex][day].quran << " ]" << " شد حيلك . " << endl;
    else
        cout << "\t     " << " حققت الهدف  " << "[ " <<  users[userIndex].quranGoal <<" / " << progress[userIndex][day].quran << " ] ✅" << " عاااش ." << endl;

    cout << endl;
    cout << "\t         ---------------------------- \n";
    if ( users[userIndex].totalPages < 604 )
        cout << "\t     " << " متبقي على الختمة القادمة : "<< 604 - users[userIndex].totalPages  << " . " << endl;
    else {
        cout << "\t       " << " تمت الختمة :) "<< endl;
        users[userIndex].totalPages = users[userIndex].totalPages - 604;
    }

    cout << endl;
    cout << "\t ------------------------------------------- \n";
    cout << endl;
    cout  << "\t\t\t" << " [ الصلوات  ]"<<endl;
    cout  << "\t\t\t" << "---------------" <<endl;
    cout << endl;
    string prayers[5] = { " الفجر "," الظهر "," العصر "," المغرب"," العشاء" };

    for (int i = 0; i < 5; i++) {

        cout << "\t       " << "صلاة" << prayers[i] << ":";
        if (progress[userIndex][day].prayersDone[i] == 1) {
            cout << " \t    " << " تم✅ " << endl;
        }

        else
            cout<<"     " << "لم يتم❌"<< endl;
    }
    cout << endl;

    cout << "\t  ------------------------------------------ \n";
    cout << endl;
    cout  << "\t\t\t" << " [ السبحة  ]"<<endl;
    cout  << "\t\t\t" << "---------------" <<endl;
    cout << endl;

    cout << "\t\t   " <<  " عدد تسبيحات اليوم : " << progress[userIndex][day].tasbeeh << endl;

    cout << "\t        ---------------------------- \n";

    if ( progress[userIndex][day].tasbeeh < users[userIndex].tasbeehGoal)
        cout << "\t    " << " لم تحقق الهدف  " << "[ " <<  users[userIndex].tasbeehGoal <<" / " << progress[userIndex][day].tasbeeh << " ]" << " شد حيلك . " << endl;
    else
        cout << "\t     " << " حققت الهدف  " << "[ " <<  users[userIndex].tasbeehGoal <<" / " << progress[userIndex][day].tasbeeh << " ] ✅" << " عاااش ." << endl;

    cout << endl;
    cout << "\t  ------------------------------------------ \n";
    cout << endl;
    cout  << "\t\t" << " [ ملخص  الأداء اليومي ]"<<endl;
    cout  << "\t\t " << "======================" <<endl;
    cout << endl;

    bool check = true ;
    for (int i = 0; i < 5; i++) {
        if (progress[userIndex][day].prayersDone[i] == 0) {
            check = false ;
            break;
        }
    }

    if (check == true)
        cout << "\t" << "        صليت كل الصلوات ✅. " << endl;
    else
        cout << "\t" << " لم تصلي الصلوات  كلها❌." << endl;

        cout << endl;

        if (progress[userIndex][day].quran >= users[userIndex].quranGoal)
            cout << "\t" << " قرأت صفحات القرآن و حققت الهدف ✅. " << endl;
        else
            cout << "\t" << "    لم تحقق هدف القرآن❌. " << endl;

        cout << endl;

        if (progress[userIndex][day].tasbeeh >= users[userIndex].tasbeehGoal)
            cout << "\t" << "      حققت هدف التسبيحات ✅. " << endl;
        else
            cout << "\t" << " لم تحقق هدف التسبيحات ❌. " << endl;

        cout << endl;

        bool quranDone = progress[userIndex][day].quran >= users[userIndex].quranGoal;
        bool tasbeehDone = progress[userIndex][day].tasbeeh >= users[userIndex].tasbeehGoal;

        if (quranDone && tasbeehDone && check)
            cout << "\t" << "      يوم ممتاز!  استمر علي كده . " << endl;
        else if (quranDone && check  ||  tasbeehDone && check) {
            cout << "\t" << "      أحب الأعمال أدومها و إن قل .   " << endl;
            cout << "\t" << "   و القليل الدائم يصنع الكثير .  " << endl;
        }
        else {
            cout << "\t" << "خير الخطائين التوابون . منتظرين أفضل الأيام المقبلة ." << endl;
            cout << "\t" << "       أثقل الأعمال على النفس أولها , و أحلاها آخرها ." << endl;
        }

        cout << "==============================================================" << endl;
}

void menu (int id) {
    int y;
    char c;

    if (id == 0) {
        do {

            cout << "\t\t ============================" <<endl;
            cout << "\t\t      القائمة  الرئيسية       " << endl;
            cout << "\t\t ============================" <<endl;
            cout << endl;

            while (true) {
                cout << "         أضغط ( 1 ) لعرض  لوحة الإنجازات اليومية" << endl;
                cout << "               أضغط ( 2 ) لعرض  تقويم شهر رمضان" << endl;
                cout << "                        أضغط ( 3 ) لعرض  الاذكار" << endl;
                cout << "                        أضغط ( 4 ) لعرض  الادعية" << endl;
                cout << "             أضغط ( 5 ) لعرض  السبحة الإلكترونية" << endl;
                cout << "أضغط ( 6 ) لإدخال الصلوات اليومية و صفحات القرآن" << endl;
                cout << "        أضغط ( 7 ) لإضافة أذكار ( خاص بالمسئول )" << endl;
                cout << "        أضغط ( 8 ) لإضافة أدعية ( خاص بالمسئول )" << endl;
                cout << "أضغط ( 9 ) لإضافة أوقات الصلوات ( خاص بالمسئول )" << endl;
                cout << "                       أضغط ( 0 ) لتسجيل الخروج" << endl;
                cout << "      :  ";

                cin >> y;
                cout << "------------------------------------------------------------" << endl;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << " Invalid input ! Please enter a number. \n ";
                    cout << "------------------------------------------------------------" << endl;
                }
                else {
                    if (y >= 0 && y <= 9)
                        break;
                }
            }

            switch (y) {
                case 0:
                    return;

                case 1:
                    dailyReport(id);
                    break;

                case 2:
                    showCalenderDay();
                    break;

                case 3:
                    showAthkar();
                    break;

                case 4:
                    showDoaa();
                    break;

                case 5:
                    rosary(id);
                    break;

                case 6:
                    updatePrayers(id);
                    break;

                case 7:
                    addThikr(id, users[id].password, users[id].name);
                    break;

                case 8:
                    addDoaa(id, users[id].password, users[id].name);
                    break;

                case 9:
                    updateCalenderDay( id , users[id].password , users[id].name);
                    break;
            }
            cout << "للرجوع للقائمة الرئيسية أضغط ( y ) :" << endl;
            cin >> c;
            cout << "------------------------------------------------------------" << endl;
        } while (c == 'y' || c == 'Y');
    }


    else {

        do {

            cout << "\t\t ============================" <<endl;
            cout << "\t\t      القائمة  الرئيسية       " << endl;
            cout << "\t\t ============================" <<endl;
            cout << endl;

            while (true) {
                cout << "         أضغط ( 1 ) لعرض  لوحة الإنجازات اليومية" << endl;
                cout << "               أضغط ( 2 ) لعرض  تقويم شهر رمضان" << endl;
                cout << "                        أضغط ( 3 ) لعرض  الاذكار" << endl;
                cout << "                        أضغط ( 4 ) لعرض  الادعية" << endl;
                cout << "             أضغط ( 5 ) لعرض  السبحة الإلكترونية" << endl;
                cout << "أضغط ( 6 ) لإدخال الصلوات اليومية و صفحات القرآن" << endl;
                cout << "                       أضغط ( 0 ) لتسجيل الخروج" << endl;
                cout << "      :  ";

                cin >> y;
                cout << "------------------------------------------------------------" << endl;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input ! Please enter a number. \n ";
                }
                else {
                    if (y >= 0 && y <= 6)
                        break;
                }
            }

            switch (y) {
                case 0:
                    return;

                case 1:
                    dailyReport(id);
                    break;

                case 2:
                    showCalenderDay();
                    break;

                case 3:
                    showAthkar();
                    break;

                case 4:
                    showDoaa();
                    break;

                case 5:
                    rosary(id);
                    break;

                case 6:
                    updatePrayers(id);
                    break;

            }
            cout << "للرجوع للقائمة الرئيسية أضغط ( y ) :" << endl;
            cin >> c;
            cout << "------------------------------------------------------------" << endl;
        } while (c == 'y' || c == 'Y');
    }
}


void saveUserData () {
    ofstream userData;
    userData.open ("users.txt", ios::out | ios::binary);


    for (int i = 0; i < userCount; i++) {
        userData << users[i].name << endl;
        userData << users[i].userID<<endl;
        userData <<  users[i].password<<endl;
        userData << users[i].hint<<endl;
        userData << users[i].tasbeehGoal<<endl;
        userData << users[i].quranGoal<<endl;
        userData << users[i].rosary<<endl;
        userData << users[i].totalPages<<endl;
        userData << users[i].points<<endl;
        userData << users[i].nickname<<endl;
        userData << "----" << endl;
    }

    userData.close();
}


void loadUserData() {
    ifstream userData("users.txt", ios::out | ios::binary);

    if (!userData)
        return;

    userCount = 0;

    while (getline(userData, users[userCount].name) && userCount < 150) {

        userData >> users[userCount].userID;
        userData.ignore();

        getline(userData, users[userCount].password);
        getline(userData, users[userCount].hint);

        userData >> users[userCount].tasbeehGoal;
        userData >> users[userCount].quranGoal;
        userData >> users[userCount].rosary;
        userData >> users[userCount].totalPages;
        userData >> users[userCount].points;
        userData.ignore();

        getline(userData, users[userCount].nickname);

        string separator;
        getline(userData, separator);

        userCount++;
    }

    userData.close();
}


void saveDoaa () {
    ofstream file("doaa.txt", ios::out | ios::binary);

    file << doaaCount << endl;

    for (int i = 0; i < doaaCount; i++) {
        file << doaalist[i].doaaID << endl;
        file << doaalist[i].content << endl;
        file << doaalist[i].category << endl;
    }

    file.close();
}


void loadDoaa () {
    ifstream file("doaa.txt", ios::out | ios::binary);

    if (!file) return;

    file >> doaaCount;
    file.ignore();

    for (int i = 0; i < doaaCount; i++) {
        file >> doaalist[i].doaaID;
        file.ignore();

        getline(file, doaalist[i].content);
        getline(file, doaalist[i].category);
    }

    file.close();
}


void saveAthkar () {
    ofstream file("thikr.txt", ios::out | ios::binary);

    file <<  thikrCount << endl;

    for (int i = 0; i < thikrCount; i++) {
        file <<  athkarlist[i].thikrID << endl;
        file <<  athkarlist[i].content << endl;
        file <<  athkarlist[i].category << endl;
        file <<  athkarlist[i].target << endl;
    }

    file.close();
}


void loadAthkar () {
    ifstream file("thikr.txt", ios::out | ios::binary);

    if (!file)
        return;

    file >> thikrCount;
    file.ignore();

    for (int i = 0; i < thikrCount; i++) {
        file >>  athkarlist[i].thikrID;
        file.ignore();

        getline(file,   athkarlist[i].content);
        getline(file,   athkarlist[i].category);

        file >> athkarlist[i].target;
        file.ignore();
    }

    file.close();
}


void saveProgress() {
    ofstream file("progress.txt");

    for (int i = 0; i < userCount; i++) {
        for (int d = 0; d < 30; d++) {
            file << progress[i][d].quran << endl;
            file << progress[i][d].tasbeeh << endl;
            for (int p = 0; p < 5; p++) {
                file << progress[i][d].prayersDone[p] << " ";
            }
            file << endl;
        }
    }
    file.close();

}


void loadProgress() {
    ifstream file("progress.txt");

    if (!file)
        return;

    for (int i = 0; i < userCount; i++) {
        for (int d = 0; d < 30; d++) {
            file >> progress[i][d].quran;
            file >> progress[i][d].tasbeeh;
            for (int p = 0; p < 5; p++) {
                file >> progress[i][d].prayersDone[p];
            }
        }
    }

    file.close();
}


void saveCalendar() {

    ofstream file("calendar.txt", ios::out | ios::binary);

    for (int i = 0; i < 30; i++) {

        file << ramadan[i].day << endl;

        for (int j = 0; j < 5; j++) {

            file << ramadan[i].times[j] << endl;
        }
        file << ramadan[i].event << endl;
        file << ramadan[i].note << endl;
        file << "----" << endl;
    }

    file.close();
}


void loadCalendar() {

    ifstream file("calendar.txt", ios::out | ios::binary);

    if (!file)
        return;

    for (int i = 0; i < 30; i++) {

        file >> ramadan[i].day;
        file.ignore();
        for (int j = 0; j < 5; j++) {
            getline(file, ramadan[i].times[j]);
        }
        getline(file, ramadan[i].event);
        getline(file, ramadan[i].note);
        string separator;
        getline(file, separator);
    }

    file.close();
}
