//getchar()需判断是否为eof或'\n'。
//while(cin.getline(s,length))可以成立，到末位自会break。另外实际输入的字符为length-1。
//在前一个cin后立刻getline会得到一个空行，这是因为cin不处理换行符。请使用cin.ignore(0x7fffffff,'\n')，无视之前的换行符。
//%0xd == 前导零#include <iostream>
//map如果访问了未包含的key，会自动创建一个。
//两个iterator不可以用大于／小于号比较。
//链表在用iterator遍历时，如果erase了元素，原来的iterator就不可用了，若要继续遍历必须使用it=list.erase(...)语句重置iterator（删除后就不用++it了）。

// openjudge 3750
// poj 3760
// 魔兽世界
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <map>
#include <list>
#define FIN(i,N) for(i=0;i<(N);++i)
#define FIN1(i,N) for(i=1;i<=(N);++i)
#define FINM(i,N) for(i=((N)-1);i>=0;--i)
#define FINM1(i,N) for(i=(N);i>=1;--i)
#define inf 1000000000 // 2*inf<2^31
#define iginf 0x7fffffff // 2147483647
#define MAX_LEN 1010
using namespace std;

int hps[5], atks[5];
int hour = 0, minute = 0;
int m, n, t; // original HP; num of cities; max time;
int WarriorNo[2] = {1,1}; // 0-red; 1-blue;
int WarriorType[2] = {0};
int cmdHP[2] = {0};
bool OccupingCMD[2] = {0}; // 0-a red warrior has taken the blue headquarter and vice versa
bool War = false;
const int WarriorOrder[2][5] = {{2,3,4,1,0},{3,0,1,2,4}};
const string TypeToName[5] = {"dragon","ninja","iceman","lion","wolf"};
const string NoToCamp[2] = {"red","blue"};

void printTime();
void createWarrior(int camp);
void warriorMarch();
void produceHP();
void earnHP();
void duel();
void announceHP();
void forgetAllThings();
// be careful with iceman!!!!!

struct warrior {
    int No = 0;   // 0-empty;
    int camp; // 0-red; 1-blue;
    int type; // 0-dragon; 1-ninja; 2-iceman; 3-lion; 4-wolf;
    int hp;
    int atk;
    bool EvenSteps = true; // for iceman
    bool ActiveAttack = true; // for wolf
} cmdWarriors[2];

struct city {
    int flag; // 0-none; 1-red; 2-blue;
    bool kill[2] = {0};
    int hp = 0;
    warrior w[2];
} cities[21]; // cities[0] is unused

void printTime() {
    printf("%03d:%02d ", hour, minute);
}

void createWarrior(int camp) {
    int no = WarriorNo[camp], type = WarriorOrder[camp][WarriorType[camp]], ReducingHP = hps[type];
    if (cmdHP[camp] < ReducingHP) return; // lacking HP, waiting for next time to create a warrior
    warrior newWarrior;
    newWarrior.No = no; newWarrior.camp = camp; newWarrior.type = type;
    newWarrior.hp = hps[type]; newWarrior.atk = atks[type];
    cmdWarriors[camp] = newWarrior;
    cmdHP[camp] -= ReducingHP;
    printTime(); printf("%s %s %d born\n", NoToCamp[camp].c_str(), TypeToName[type].c_str(), no);
    if (++WarriorType[camp] == 5) WarriorType[camp] = 0;
    ++WarriorNo[camp];
    // warrior born successfully
}

void warriorMarch() {
    int i, j, type;
    warrior tempw[21][2], emptyw;
    // iceman
    FIN(j,2) {
        if (cmdWarriors[j].type == 2) {
            cmdWarriors[j].EvenSteps = false; // this must be his first step
        }
    }
    FIN1(i,n) {
        tempw[i][0] = cities[i].w[0];
        tempw[i][1] = cities[i].w[1];
        cities[i].w[0] = cities[i].w[1] = emptyw; // first clear all the warriors
        // iceman
        FIN(j,2) {
            if (tempw[i][j].type != 2) continue;
            tempw[i][j].EvenSteps = !tempw[i][j].EvenSteps;
            if (tempw[i][j].EvenSteps) {
                tempw[i][j].hp -= 9;
                if (tempw[i][j].hp <= 0) tempw[i][j].hp = 1;
                tempw[i][j].atk += 20;
            }
        }
    }
    // blue warrior takes the red headquarter
    if (tempw[1][1].No) {
        type = tempw[1][1].type;
        printTime();
        printf("blue %s %d reached red headquarter with %d elements and force %d\n",
               TypeToName[type].c_str(), tempw[1][1].No, tempw[1][1].hp, tempw[1][1].atk);
        if (OccupingCMD[1]) {
            printTime(); printf("red headquarter was taken\n");
            War = false;
        }
        OccupingCMD[1] = true;
    }
    FIN1(i,n) {
        // red warrior march (from headquarter)
        if (i == 1) {
            if (cmdWarriors[0].No) {
                type = cmdWarriors[0].type;
                printTime();
                printf("red %s %d marched to city 1 with %d elements and force %d\n",
                       TypeToName[type].c_str(), cmdWarriors[0].No,
                       cmdWarriors[0].hp, cmdWarriors[0].atk);
            }
            cities[1].w[0] = cmdWarriors[0];
            cmdWarriors[0] = emptyw;
        } else {
            // red warrior march
            if (tempw[i-1][0].No) {
                type = tempw[i-1][0].type;
                printTime();
                printf("red %s %d marched to city %d with %d elements and force %d\n",
                       TypeToName[type].c_str(), tempw[i-1][0].No, i,
                       tempw[i-1][0].hp, tempw[i-1][0].atk);
            }
            cities[i].w[0] = tempw[i-1][0];
        }
        if (i != n) {
            // blue warrior march
            if (tempw[i+1][1].No) {
                type = tempw[i+1][1].type;
                printTime();
                printf("blue %s %d marched to city %d with %d elements and force %d\n",
                       TypeToName[type].c_str(), tempw[i+1][1].No, i,
                       tempw[i+1][1].hp, tempw[i+1][1].atk);
            }
            cities[i].w[1] = tempw[i+1][1];
        } else {
            // blue warrior march (from headquarter)
            if (cmdWarriors[1].No) {
                type = cmdWarriors[1].type;
                printTime();
                printf("blue %s %d marched to city %d with %d elements and force %d\n",
                       TypeToName[type].c_str(), cmdWarriors[1].No, n,
                       cmdWarriors[1].hp, cmdWarriors[1].atk);
            }
            cities[n].w[1] = cmdWarriors[1];
            cmdWarriors[1] = emptyw;
        }
    }
    // red warrior takes the blue headquarter
    if (tempw[n][0].No) {
        type = tempw[n][0].type;
        printTime();
        printf("red %s %d reached blue headquarter with %d elements and force %d\n",
               TypeToName[type].c_str(), tempw[n][0].No, tempw[n][0].hp, tempw[n][0].atk);
        if (OccupingCMD[0]) {
            printTime(); printf("blue headquarter was taken\n");
            War = false;
        }
        OccupingCMD[0] = true;
    }
}

void produceHP() {
    int i;
    FIN1(i,20) {
        cities[i].hp += 10;
    }
}

void earnHP() {
    int i, c = -1, type;
    FIN1(i,20) {
        if (cities[i].w[0].No && !cities[i].w[1].No) c = 0;
        if (cities[i].w[1].No && !cities[i].w[0].No) c = 1;
        if (c != -1) {
            cmdHP[c] += cities[i].hp;
            type = cities[i].w[c].type;
            printTime(); printf("%s %s %d earned %d elements for his headquarter\n",
                   NoToCamp[c].c_str(), TypeToName[type].c_str(),
                   cities[i].w[c].No, cities[i].hp);
            cities[i].hp = 0;
        }
        c = -1;
    }
}

void duel() {
    int i, rtype, btype, rhp, bhp;
    warrior emptyw, *tmp;
    int slain[21][2] = {0};
    bool camp = 0;
    FIN1(i,n) {
        warrior *r = &cities[i].w[0], *b = &cities[i].w[1]; camp = 0;
        if (r->No && b->No) {
            if (cities[i].flag == 2 || (!cities[i].flag && !(i%2))) { // blue barrior attacks first
                // swap r and b
                tmp = r; r = b; b = tmp; camp = 1;
            }
            rtype = r->type; btype = b->type; rhp = r->hp; bhp = b->hp;
            // the following comments are based on that red barrior attacks first
            printTime();
            printf("%s %s %d attacked %s %s %d in city %d with %d elements and force %d\n",
                   NoToCamp[camp].c_str(), TypeToName[rtype].c_str(), r->No,
                   NoToCamp[!camp].c_str(), TypeToName[btype].c_str(), b->No,
                   i, r->hp, r->atk);
            b->hp -= r->atk;
            if (b->hp <= 0) { // blue barrior is slain
                printTime(); printf("%s %s %d was killed in city %d\n",
                                    NoToCamp[!camp].c_str(), TypeToName[btype].c_str(),
                                    b->No, i);
                // wolf
                if (r->type == 4) {
                    r->ActiveAttack = !r->ActiveAttack;
                    if (r->ActiveAttack) { r->hp *= 2; r-> atk *= 2; };
                }
                // the poor lion's blood is sucked by his enemy
                if (b->type == 3) r->hp += bhp;
                *b = emptyw;
                slain[i][camp] = cities[i].hp;
                cities[i].hp = 0;
                
            } else { // blue barrior will beat back
                if (btype != 1) { // ninja is so weak!
                    printTime();
                    printf("%s %s %d fought back against %s %s %d in city %d\n",
                           NoToCamp[!camp].c_str(), TypeToName[btype].c_str(), b->No,
                           NoToCamp[camp].c_str(), TypeToName[rtype].c_str(), r->No, i);
                    r->hp -= b->atk / 2;
                    if (r->hp <= 0) {
                        printTime(); printf("%s %s %d was killed in city %d\n",
                                            NoToCamp[camp].c_str(), TypeToName[rtype].c_str(),
                                            r->No, i);
                        if (r->type == 3) b->hp += rhp;
                        *r = emptyw;
                        slain[i][!camp] = cities[i].hp;
                        cities[i].hp = 0;
                    }
                }
            }
            if (r->No && !rtype) { // living dragon will yell
                printTime(); printf("%s dragon %d yelled in city %d\n",
                                    NoToCamp[camp].c_str(), r->No, i);
            }
            // announce first and add hp later
            if (slain[i][camp]) {
                printTime(); printf("%s %s %d earned %d elements for his headquarter\n",
                                    NoToCamp[camp].c_str(), TypeToName[rtype].c_str(),
                                    r->No, slain[i][camp]);
                // raise flags
                if (cities[i].kill[camp] && cities[i].flag != camp + 1) {
                    cities[i].flag = camp + 1;
                    printTime(); printf("%s flag raised in city %d\n",
                                        NoToCamp[camp].c_str(), i);
                }
                cities[i].kill[camp] = !cities[i].kill[camp];
                cities[i].kill[!camp] = false;
            }
            if (slain[i][!camp]) {
                printTime(); printf("%s %s %d earned %d elements for his headquarter\n",
                       NoToCamp[!camp].c_str(), TypeToName[btype].c_str(),
                       b->No, slain[i][!camp]);
                if (cities[i].kill[!camp] && cities[i].flag != !camp + 1) {
                    cities[i].flag = !camp + 1;
                    printTime(); printf("%s flag raised in city %d\n",
                                        NoToCamp[!camp].c_str(), i);
                }
                cities[i].kill[!camp] = !cities[i].kill[!camp];
                cities[i].kill[camp] = false;
            }
            // there was a duel but no dead barriors
            if (!slain[i][camp] && !slain[i][!camp] && r->No && b->No)
                cities[i].kill[!camp] = cities[i].kill[camp] = false;
        }
    }
    // aword red barriors
    FINM1(i,n) {
        if (slain[i][0]) {
            if (cmdHP[0] >= 8) {
                cmdHP[0] -= 8;
                cities[i].w[0].hp += 8;
            } else break;
        }
    }
    // aword blue barriors
    FIN1(i,n) {
        if (slain[i][1]) {
            if (cmdHP[1] >= 8) {
                cmdHP[1] -= 8;
                cities[i].w[1].hp += 8;
            } else break;
        }
    }
    // add HP to headquarters
    FIN1(i,n) {
        if (slain[i][0]) {
            cmdHP[0] += slain[i][0];
        } else if (slain[i][1]) {
            cmdHP[1] += slain[i][1];
        }
    }
}

void announceHP() {
    printTime(); printf("%d elements in red headquarter\n", cmdHP[0]);
    printTime(); printf("%d elements in blue headquarter\n", cmdHP[1]);
}

void forgetAllThings() {
    int i;
    warrior emptyw;
    hour = 0, minute = 0;
    WarriorNo[0] = WarriorNo[1] = 1;
    WarriorType[0] = WarriorType[1] = 0;
    OccupingCMD[0] = OccupingCMD[1] = 0;
    FIN1(i,20) {
        cities[i].flag = cities[i].kill[0] = cities[i].kill[1] = cities[i].hp = 0;
        cities[i].w[0] = cities[i].w[1] = cmdWarriors[0] = cmdWarriors[1] = emptyw;
    }
    War = false;
}

int main() {
    int cases,i;
    cin >> cases;
    FIN1(i,cases){
        cin >> m >> n >> t;
        cin >> hps[0] >> hps[1] >> hps[2] >> hps[3] >> hps[4];
        cin >> atks[0] >> atks[1] >> atks[2] >> atks[3] >> atks[4];
        printf("Case:%d\n",i);
        forgetAllThings();
        cmdHP[0] = cmdHP[1] = m;
        War = true;
        for (minute = 0; hour * 60 + minute <= t; minute += 10) {
            if (minute == 60) { minute = 0; ++hour; }
            switch (minute) {
                case 0:
                createWarrior(0); createWarrior(1);
                break;
                case 10:
                warriorMarch();
                break;
                case 20:
                produceHP();
                break;
                case 30:
                earnHP();
                break;
                case 40:
                duel();
                break;
                case 50:
                announceHP();
                break;
                default:break;
            }
            if (!War) break;
        }
    }
    return 0;
}
