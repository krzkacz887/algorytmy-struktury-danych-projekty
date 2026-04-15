#include <iostream>
#include <string>
using namespace std;

int sprOpR(char plansza[11][11], bool hist[11][11], int dPlanszy, int x, int y) {
	int opcje[6][2] = { {0,-1},{-1,-1},{-1,0},{1,1},{0,1},{1,0} };
	int Nx, Ny;
	if (y == dPlanszy - 1 && plansza[x][y] == 'r')return 1;
	for (int i = 0; i < 6; i++) {
		Nx = x + opcje[i][0];
		Ny = y + opcje[i][1];
		if (Ny >= 0 && Ny <= dPlanszy - 1 && Nx >= 0 && Nx <= dPlanszy - 1) {
			if (plansza[Nx][Ny] == 'r' && hist[Nx][Ny] != 1) {
				hist[Nx][Ny] = 1;
				if (sprOpR(plansza, hist, dPlanszy, Nx, Ny)) return 1;
			}
		}
	}
	return 0;
}
int sprOpB(char plansza[11][11], bool hist[11][11], int dPlanszy, int x, int y) {
	int opcje[6][2] = { {0,-1},{-1,-1},{-1,0},{1,1},{1,0},{0,1} };
	int Nx, Ny;
	if (x == dPlanszy -1 && plansza[x][y] == 'b') return 1;
	for (int i = 0; i < 6; i++) {
		Nx = x + opcje[i][0];
		Ny = y + opcje[i][1];
		if (Ny >= 0 && Ny <= dPlanszy - 1 && Nx >= 0 && Nx <= dPlanszy - 1) {
			if (plansza[Nx][Ny] == 'b' && hist[Nx][Ny] != 1) {
				hist[Nx][Ny] = 1;
				if (sprOpB(plansza, hist, dPlanszy, Nx, Ny)) return 1;
			}
		}
	}
	return 0;
}
int koniecG(char plansza[11][11], int red, int blue,int dPlanszy) {
	if (red == blue || (red - 1) == blue) {
		bool hist2[11][11] = { 0 };
		for (int i = 0; i < dPlanszy; i++) {
			if (plansza[0][i] == 'b') {
				hist2[0][i] = 1;
				if (sprOpB(plansza, hist2, dPlanszy, 0, i)) return 3;
			}
		}
		bool hist1[11][11] = { 0 };
		if (dPlanszy == 1 && plansza[0][0] == 'r') return 2;

		for (int i = 0; i < dPlanszy; i++) {
			if (plansza[i][0] == 'r') {
				hist1[i][0] = 1;
				if (sprOpR(plansza, hist1, dPlanszy, i, 0)) return 2;
			}
		}
	}
	return 0;
}

int isPoss(char plansza[11][11], int red, int blue, int dPlanszy) {
	if (red == blue || (red - 1) == blue) {
		if (koniecG(plansza, red, blue, dPlanszy) == 0) return 1;
		else if (koniecG(plansza, red, blue, dPlanszy) == 2) {
			if ((red - 1) != blue) return 0;
			else {
				int licz = 0;
				for (int i = 0; i < dPlanszy; i++) {
					for (int j = 0; j < dPlanszy; j++) {
						if (plansza[i][j] == 'r') {
							plansza[i][j] = ' ';
							if (koniecG(plansza, red, blue, dPlanszy) == 2) {
								licz++;
							}
							plansza[i][j] = 'r';
						}
					}
				}
				if (licz == red)return 0;
				else return 1;
			}
		}
		else if (koniecG(plansza, red, blue, dPlanszy) == 3) {
			if (red != blue) return 0;
			else {
				int licz = 0;
				for (int i = 0; i < dPlanszy; i++) {
					for (int j = 0; j < dPlanszy; j++) {
						if (plansza[i][j] == 'b') {
							plansza[i][j] = ' ';
							if (koniecG(plansza, red, blue, dPlanszy) == 3) {
								licz++;
							}
							plansza[i][j] = 'b';
						}
					}
				}
				if (licz == blue)return 0;
				else return 1;
			}
		}
		else return 0;
	}
	else return 0;
}
int main() {
	string lin;
	char perm[11]="";
	int dPlanszy = 0, stanC = 0, red=0,blue=0,puste=0,ktlinia=0,lperm=0;
	char plansza[11][11];
	while (getline(cin, lin)) {
		if (lin[0] == 0)cout << endl;
		if (lin[0] >= 65 && lin[0] <= 90) {
			stanC = 0;
		}
		if (lin[0] == ' ' && stanC == 0) {
			stanC = 1;
			ktlinia = 0;
			red = 0;
			blue = 0;
			while (lin[dPlanszy] == ' ')dPlanszy++;
			dPlanszy = (dPlanszy - 1) / 3 + 1;
		}
		if (stanC == 1) {
			for (int i = 0; i < lin.size() - 2; i++) {
				if (lin[i] == 'r') {
					red++;
					perm[lperm] = 'r';
					lperm++;
				}
				if (lin[i] == 'b') {
					blue++;
					perm[lperm] = 'b';
					lperm++;
				}
				if (lin[i] == '<' && lin[i + 1] == ' ' && lin[i + 2] == ' ') {
					puste++;
					perm[lperm] = 'P';
					lperm++;
				}
			}
			if (ktlinia <= dPlanszy) {
				//cout << ktlinia << endl;
				int licz = ktlinia;
				while (licz > 0) {
					plansza[licz - 1][ktlinia - licz] = perm[ktlinia - licz];
					licz--;
				}
			}
			if (ktlinia > dPlanszy) {
				//cout << 2 * dPlanszy - ktlinia << endl;
				int licz = 0;
				while (licz < 2 * dPlanszy - ktlinia) {
					plansza[dPlanszy - licz - 1][ktlinia - dPlanszy + licz] = perm[licz];
					licz++;
				}
			}
			ktlinia++;
			lperm = 0;
		}
		if (stanC == 0) {
			if (lin.compare("BOARD_SIZE") == 0) cout << dPlanszy << endl;
			if (lin.compare("PAWNS_NUMBER") == 0) cout << red + blue << endl;
			if (lin.compare("IS_BOARD_CORRECT") == 0) {
				if (red == blue || (red - 1) == blue) cout << "YES" << endl;
				else cout << "NO" << endl;
			}
			if (lin.compare("IS_GAME_OVER") == 0) {
				if (koniecG(plansza, red, blue, dPlanszy)==2)cout << "YES RED" << endl;
				else if(koniecG(plansza, red, blue, dPlanszy) == 3)cout << "YES BLUE" << endl;
				else cout << "NO" << endl;
			}
			if (lin.compare("IS_BOARD_POSSIBLE") == 0) {
				if (isPoss(plansza, red, blue, dPlanszy))cout << "YES" << endl;
				else cout << "NO" << endl;
			}
		}
	}
	return 0;
}
