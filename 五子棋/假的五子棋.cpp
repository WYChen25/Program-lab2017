#include "Define.h"
#include "Square.h"
#include "ClientSocket.h"
#include "Gobang.h"
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include<fstream>

FILE *sfile = fopen("chees.txt", "w");

#define random(x) (rand()%x)
#define ROWS 15
#define COLS 15
#define ROUNDS 2

Square board[ROWS][COLS];
int ownColor = -1, oppositeColor = -1;		
int STEP = 1;
char lastmsg[16] = { "" };
int own[ROWS][COLS];
int opps[ROWS][COLS];
int scor[ROWS][COLS];					//定义三个数组，一个存放自己的棋盘，一个对面的棋盘，一个计分。

void authorize(const char *id, const char *pass) {
	connectServer();
	std::cout << "Authorize " << id << std::endl;
	char msgBuf[BUFSIZE];
	memset(msgBuf, 0, BUFSIZE);
	msgBuf[0] = 'A';
	memcpy(&msgBuf[1], id, 9);
	memcpy(&msgBuf[10], pass, 6);
	int rtn = sendMsg(msgBuf);
	// printf("Authorize Return %d\n", rtn);
	if (rtn != 0) printf("Authorized Failed\n");
}

void gameStart() {
	char id[12], passwd[10];
	std::cout << "ID: " << std::endl;
	std::cin >> id;
	std::cout << "PASSWD: " << std::endl;
	std::cin >> passwd;
	authorize(id, passwd);
	std::cout << "Game Start" << std::endl;
	for (int round = 0; round < ROUNDS; round++) {
		fprintf(sfile, "%s", "newround");
		roundStart(round);
		oneRound();
		roundOver(round);
	}
	gameOver();
	close();
}

void gameOver() {
	std::cout << "Game Over" << std::endl;
}

void roundStart(int round) {
	std::cout << "Round " << round << " Ready Start" << std::endl;
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			board[r][c].reset();
		}
	}
	memset(lastmsg, 0, sizeof(lastmsg));
	int rtn = recvMsg();
	if (rtn != 0) return;
	if (strlen(recvBuf) < 2)
		printf("Authorize Failed\n");
	else
	    printf("Round start received msg %s\n", recvBuf);
	switch (recvBuf[1]) {
		case 'B':
			ownColor = 0;
			oppositeColor = 1;
			rtn = sendMsg("BB");
			if (rtn != 0) return;
			break;
		case 'W':
			ownColor = 1;
			oppositeColor = 0;
			rtn = sendMsg("BW");
			std::cout << "Send BW" << rtn << std::endl;
			if (rtn != 0) return;
			break;
		default:
			printf("Authorized Failed\n");
			break;
		}
}

void oneRound() {
	int DIS_FREQ = 5;
	STEP = 1;
	switch (ownColor) {
	case 0:
		while (STEP < 10000) { 

			if (STEP != 1 && (STEP-1) % DIS_FREQ == 0) {
				int ret = observe();       // self disappeared
				if (ret >= 1) break;
				else if (ret != -8) {
					std::cout << "ERROR: Not Self(BLACK) Disappeared" << std::endl;
				}
			}
			step();                        // take action, send message
			
			if (observe() >= 1) break;     // receive RET Code
										   // saveChessBoard();
			if (STEP != 1 && (STEP-1) % DIS_FREQ == 0) {
				int ret = observe();       // see white disappear
				if (ret >= 1) break;
				else if (ret != -9) {
					std::cout << ret << " ERROR: Not White Disappeared" << std::endl;
				}
			}
			
			if (observe() >= 1) break;    // see white move
			STEP++;
			// saveChessBoard();
		}
		printf("One Round End\n");
		break;
	case 1:
		while (STEP < 10000) {

			if (STEP != 1 && (STEP-1) % DIS_FREQ == 0) {
				int ret = observe();       // black disappeared
				if (ret >= 1) break;
				else if (ret != -8) {
					std::cout << "ERROR: Not Black Disappeared" << std::endl;
				}
			}
			if (observe() >= 1) break;    // see black move

			if (STEP != 1 && (STEP-1) % DIS_FREQ == 0) {
				int ret = observe();      // self disappeared
				if (ret >= 1) break;
				else if (ret != -9) {
					std::cout << "ERROR: Not Self Disappeared" << std::endl;
				}
			}

			step();                        // take action, send message
			if (observe() >= 1) break;     // receive RET Code
										   // saveChessBoard();
			STEP++;
		}
		printf("One Round End\n");
		break;
    default:
		break;
    }
}

void roundOver(int round) {
	std::cout << "Round " << round << " Over" << std::endl;
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			//std::cout << own[r][c] << "  ";
			own[r][c] = 0;
		}
		//std::cout << std::endl;
	}
	//std::cout << std::endl;
	//std::cout << std::endl;
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			//std::cout << opps[r][c] << "  ";
			opps[r][c] = 0;
		}
		//std::cout << std::endl;
	}
	//std::cout << std::endl;
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			//std::cout << scor[r][c] << "  ";
			scor[r][c] = 0;
		}
		//std::cout << std::endl;
	}
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			board[r][c].reset();
		}
		//std::cout << std::endl;
	}
	ownColor = oppositeColor = -1;
}

void lastMsg() {
	printf(lastmsg);
	puts("");
}

int observe() {
	int rtn = 0;
	int recvrtn = recvMsg();
	if (recvrtn != 0) return 1;
	printf("receive msg %s\n", recvBuf);
	switch (recvBuf[0]) {
	case 'R':   // return messages
	{
		switch (recvBuf[1]) {
		case '0':    // valid step
			switch (recvBuf[2]) {
				case 'P':   // update chessboard
				{
					int desRow = (recvBuf[3] - '0') * 10 + recvBuf[4] - '0';
					int desCol = (recvBuf[5] - '0') * 10 + recvBuf[6] - '0';
					board[desRow][desCol].color = recvBuf[7] - '0';
					if (board[desRow][desCol].color == ownColor) {
						own[desRow][desCol] = STEP;						//记录步骤至自己的棋盘，后同；
					}
					else {
						opps[desRow][desCol] = STEP;
					}
					board[desRow][desCol].empty = false;
					memcpy(lastmsg, recvBuf, strlen(recvBuf));
					break;
				}
				case 'D':   // Disappeared
				{
					int desRow = (recvBuf[3] - '0') * 10 + recvBuf[4] - '0';
					int desCol = (recvBuf[5] - '0') * 10 + recvBuf[6] - '0';
					if (board[desRow][desCol].color == ownColor) {
						own[desRow][desCol] = 0;
					}
					else {
						opps[desRow][desCol] = 0;
					}
					board[desRow][desCol].color = -1;
					board[desRow][desCol].empty = true;
					if (recvBuf[7] - '0' == 0)  // black disappear
						rtn = -8;
					else
						rtn = -9;
					memcpy(lastmsg, recvBuf, strlen(recvBuf));
					break;
				}
				case 'N':   // R0N: enemy wrong step
				{
					break;
				}
			}
			break;
		case '1':
			std::cout << "Error -1: Msg format error\n";
			rtn = -1;
			break;
		case '2':
			std::cout << "Error -2: Coordinate error\n";
			rtn = -2;
			break;
		case '4':
			std::cout << "Error -4: Invalid step\n";
			rtn = -4;
			break;
		default:
			std::cout << "Error -5: Other error\n";
			rtn = -5;
			break;
		}
		break;
	}
	case 'E':
	{
		switch (recvBuf[1]) {
			case '0':
				// game over
				rtn = 2;
				break;
			case '1':
				// round over
				rtn = 1;
			default:
				break;
			}
			break;
		}
	}
	return rtn;
}

void putDown(int row, int col) {
	char msg[6];
	memset(msg, 0, sizeof(msg));
	msg[0] = 'S';
	msg[1] = 'P';
	msg[2] = '0' + row / 10;
	msg[3] = '0' + row % 10;
	msg[4] = '0' + col / 10;
	msg[5] = '0' + col % 10;
	board[row][col].color = ownColor;
	board[row][col].empty = false;
	lastMsg();
	printf("put down (%c%c, %c%c)\n", msg[2], msg[3], msg[4], msg[5]);
	sendMsg(msg);
}

void noStep() {
	sendMsg("SN");
	printf("send msg %s\n", "SN");
}

void saveChessBoard() {
	
}

void step() {

	int r = 0, c = 0;
	// printf("%s\n", lastMsg());
	score();
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (scor[r][c] < scor[i][j] && own[i][j] == 0 && opps[i][j] == 0) {
				r = i;
				c = j;
			}
		}
	}
	if (own[r][c] != 0 || opps[r][c] != 0) {
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				if (own[i][j] == 0 && opps[i][j] == 0) {
					r = i;
					c = j;
					break;
				}
			}
		}
	}
	serve();
	putDown(r, c);
	// noStep();
}

void score() {
	bool flag = false;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (own[i][j] != 0 && own[i][j + 1] != 0 && own[i][j + 2] != 0 && own[i][j + 3] != 0) {
				if((j +4) < COLS)
					scor[i][j + 4] = 2000;
				if (j > 0)
					scor[i][j - 1] = 2000;
			}
			else if (own[i][j] != 0 && own[i - 1][j] != 0 && own[i - 2][j] != 0 && own[i - 3][j] != 0) {
				if((i - 4) >= 0 )
					scor[i - 4][j] = 2000;
				if ((i + 1) < ROWS)
					scor[i + 1][j] = 2000;
			}
			else if (own[i][j] != 0 && own[i - 1][j + 1] != 0 && own[i - 2][j + 2] != 0 && own[i - 3][j + 3] != 0) {
				if((j + 4) < COLS && (i - 4) >= 0)
					scor[i - 4][j + 4] = 2000;
				if ((j - 1) > 0 && (i + 1) < ROWS)
					scor[i + 1][j - 1] = 2000;
			}
			else if (opps[i][j] != 0 && opps[i][j + 1] != 0 && opps[i][j + 2] != 0 && opps[i][j + 3] != 0) {
				if ((j + 4) < COLS && scor[i][j + 4] < 1900) 
					scor[i][j + 4] = 1900;
				if (j > 0 && scor[i][j-1] < 1900) 
					scor[i][j - 1] = 1900;
			}
			else if (opps[i][j] != 0 && opps[i - 1][j] != 0 && opps[i - 2][j] != 0 && opps[i - 3][j] != 0) {
				if ((i - 4) >= 0 && scor[i - 4][j] < 1900)
					scor[i - 4][j] = 1900;
				if ((i + 1) < ROWS && scor[i + 1][j] < 1900)
					scor[i + 1][j] = 1900;
			}
			else {
				if (scor[i][j] < 1) 
					scor[i][j] = 1;
			}
			int temp = 0;
			if ((i == 7 || i == 8) && (j == 7 || j == 8)) {
				temp = temp + 4;
			}
			else if (i > 5 && i < 10 && j > 5 && j < 10) {
				temp = temp + 1;
			}
			else
				temp = temp;
			for (int m = max(0, i - 4); m < min(ROWS, i + 4); m++) {
				if (opps[m][j] != 0) {
					switch (abs(i - m)) {
					case 1:temp = temp + 100;
					case 2:temp = temp + 90;
					case 3:temp = temp + 70;
					case 4:temp = temp + 50;
					default:temp = temp ;
					}
				}
			}
			for (int n = max(0, j - 4); n < min(COLS, j + 4); n++) {
				if (opps[i][n] != 0) {
					switch (abs(j - n)) {
					case 1:temp = temp + 100;
					case 2:temp = temp + 90;
					case 3:temp = temp + 70;
					case 4:temp = temp + 50;
					default:temp = temp;
					}
				}
			}
			for (int x = max(0, i - 4); x < min(ROWS, i + 4); x++) {
				for (int y = max(0, j - 4); y < min(COLS, j + 4); y++) {
					if ((y - j) == (x - i) && opps[x][y] != 0) {
						switch (abs(y - j)) {
						case 1:temp = temp + 100;
						case 2:temp = temp + 90;
						case 3:temp = temp + 70;
						case 4:temp = temp + 50;
						default:temp = temp;
						}
					}
				}
			}

			for (int m = max(0, i - 4); m < min(ROWS, i + 4); m++) {
				if (own[m][j] != 0) {
					switch (abs(i - m)) {
					case 1:temp = temp + 95;
					case 2:temp = temp + 85;
					case 3:temp = temp + 65;
					case 4:temp = temp + 45;
					default:temp = temp;
					}
				}
			}

			for (int n = max(0, j - 4); n < min(COLS, j + 4); n++) {
				if (own[i][n] != 0) {
					switch (abs(j - n)) {
					case 1:temp = temp + 95;
					case 2:temp = temp + 85;
					case 3:temp = temp + 65;
					case 4:temp = temp + 45;
					default:temp = temp;
					}
				}
			}

			for (int x = max(0, i - 4); x < min(ROWS, i + 4); x++) {
				for (int y = max(0, j - 4); y < min(COLS, j + 4); y++) {
					if (abs(y - j) == abs(x - i) && own[x][y] != 0) {
						switch (abs(y - j)) {
						case 1:temp = temp + 95;
						case 2:temp = temp + 85;
						case 3:temp = temp + 65;
						case 4:temp = temp + 45;
						default:temp = temp;
						}
					}
				}
			}
			
			if (temp > scor[i][j]) {
				scor[i][j] = temp;
			}


		}
	}

}

void serve()
{
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (own[i][j] != 0) {
				fprintf(sfile, "%s", "#");
				fprintf(sfile, "%s", "|");
			}
			else if (opps[i][j] != 0) {
				fprintf(sfile, "%s", "*");
				fprintf(sfile, "%s", "|");
			}
			else {
				fprintf(sfile, "%s", " ");
				fprintf(sfile, "%s", "|");
			}
		}
		fprintf(sfile, "%s", "\n");
		for (int m = 0; m < ROWS; m++) {
			fprintf(sfile, "%s", "——");
		}
		fprintf(sfile, "%s", "\n");
	}
	for (int i = 0; i < 20; i++) {
		fprintf(sfile, "%s", "^^^");
	}
	fprintf(sfile, "%s", "\n");
}

