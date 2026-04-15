#include <iostream>
#include<stdio.h>
#include<cmath>
#include<cstring>
using namespace std;

struct Lista {
	char wyr[10];
	int wart=0;
	Lista* next;
};

Lista* nowaLista(char wyr[10]) {
	Lista* nowaLista = new Lista;
	for(int i=0;i<10;i++)nowaLista->wyr[i] = wyr[i];
	nowaLista->next = nullptr;
	return nowaLista;
}
void put(char wyr[10], Lista*& head) {
		Lista* nowyEl = nowaLista(wyr);
		Lista* temp = head;
		while (temp != nullptr) {
			if (temp->next == nullptr)break;
			temp = temp->next;
		}
		if (temp != nullptr)temp->next = nowyEl;
}
void push(char wyr[10], Lista*& head) {
		Lista* nowyEl = nowaLista(wyr);
		nowyEl->next = head;
		head = nowyEl;
}

void zmWart(Lista*& head, int wart) {
	head->wart = wart;
}
void usunEl(Lista*& head) {
	if (head == nullptr) return;
	Lista* temp = head;
	head = head->next;
	delete temp;
	return;
}
void usunOst(Lista*& head) {
	Lista* temp = head;
	while (temp->next->next != nullptr) {
		temp = temp->next;
	}
	delete temp->next;
	temp->next = nullptr;
}
void wypiszL2(Lista* head) {
	Lista* temp = head;
	while (temp != nullptr) {
		if (temp->wyr[0] == 'x')cout << temp->wart;
		else {
			for (int i = 0; i < strlen(temp->wyr); i++)cout << temp->wyr[i];
		}
		cout << "  ";
		temp = temp->next;
	}
	cout << endl;
}
void wypiszL1(Lista* head) {
	Lista* temp = head;
	while (temp != nullptr) {
		if (temp->wyr[0] == 'x')cout << temp->wart;
		else {
			for (int i = 0; i < strlen(temp->wyr); i++)cout << temp->wyr[i];
		}
		cout << " ";
		temp = temp->next;
	}
	cout << endl;
}
int strtoint(char sl[10]) {
	int wyn = 0;
	int dl = int(strlen(sl));
	for (int i = 0; i<dl; i++) {
		wyn += (int(sl[i])-48) * int(pow(10, dl-i-1));
	}
	return wyn;
}
void delListe(Lista*& head) {
	while (head != nullptr) {
		Lista* temp = head;
		head = head->next;
		delete temp;
	}
	delete head;
}
char znak1(Lista*& head) {
	return head->wyr[0];
}
void pop(Lista*& head, char* slo) {
	int i = 0;
	for (i = 0; i < int(strlen(head->wyr)); i++) {
		slo[i] = head->wyr[i];
	}
	slo[i] = '\0';
	usunEl(head);
}
int popint(Lista*& head) {
	int liczba = head->wart;
	usunEl(head);
	return liczba;
}


int prior(char slo[10]) {
	char wyb = slo[0];
	if (wyb == '+' || wyb == '-')return 1;
	if (wyb == '*' || wyb == '/')return 2;
	if (wyb == 'N')return 3;
	if (wyb == '(' || wyb == ')')return 5;
	else return 4;
}

void dod1(Lista*& head) {
	head->wyr[0]++;
}

int main() {
	int ile = 0;
	cin >> ile;

	for (int m = 0; m < ile; m++) {
		char pob[10] = "onp";
		char prze[10] = "1";
		char nawL[10] = "(";
		char czyint[10] = "x";
		Lista* stack = new Lista;
		stack = nullptr;
		Lista* onp = nowaLista(pob);
		Lista* przec = nowaLista(prze);
		int czyOtwartoNawias = 0, liczba=0, brk=0;
		while (true) {
			cin >> pob;
			if (pob[0] == '.')break;
			if (stack != nullptr)if (pob[0] == '(' && (znak1(stack) == 'M' || znak1(stack) == 'I')) {
				czyOtwartoNawias = 1;
			}
			if (pob[0] >= 48 && pob[0] <= 57) {
				put(pob, onp);//put
			}
			//if liczba
			else if (pob[0] == ',') {
				if (czyOtwartoNawias == 1) {
					while (stack != nullptr) {
						pop(stack, pob);
						if (pob[0] == '(')break;
						if (pob[0] == 'M') {
							pob[3] = znak1(przec);
							put(pob, onp);
						}
						else put(pob, onp);
						if (pob[0] == 'M' || pob[0] == 'I')usunEl(przec);
					}
					czyOtwartoNawias = 0;
				}
				if (czyOtwartoNawias == 0) {
					czyOtwartoNawias = 1;
					push(nawL, stack);
				}
				dod1(przec);
			}
			//if przecinek
			else if (pob[0] == '(') {
				if (stack != nullptr)push(pob, stack);
			}
			else if (pob[0] == ')') {
				while (stack != nullptr) {
					pop(stack, pob);
					if (pob[0] == '(')break;
					if (pob[0] == 'M') {
						pob[3] = znak1(przec);
						put(pob, onp);
					}
					else put(pob, onp);
					if (pob[0] == 'M' || pob[0] == 'I') usunEl(przec);
				}
			}
			//if nawias
			else {
				if (pob[0] == 'M' || pob[0] == 'I')push(prze, przec);
				int prio = prior(pob);
				char top[10] = " ";
				if (stack != nullptr) {
					if (znak1(stack) == 'N' && pob[0] == 'N') {
						prio++;
					}
				}
				while (stack != nullptr) {
					pop(stack, top);
					if (top[0] == '(' || prior(top) < prio) {
						push(top, stack);
						break;
					}
					if (top[0] == 'M') {
						top[3] = znak1(przec);
					}
					if (top[0] == 'M' || top[0] == 'I') usunEl(przec);
					put(top, onp);
				}
				push(pob, stack);
			}
			//if operacja

		}
		while (stack != nullptr) {
			pop(stack, pob);
			if (pob[0] == 'M') {
				pob[3] = znak1(przec);
				put(pob, onp);
				usunEl(przec);
			}
			else if (pob[0] != '(') put(pob, onp);


		}
		usunEl(onp);
		//usunEl(stack);
		wypiszL2(onp);
		//zrobienie onp
		while (onp != nullptr) {
			pop(onp, pob);
			if (pob[0] >= '0' && pob[0] <= '9') {
				liczba = strtoint(pob);
				pob[0] = 'x';
				push(pob, stack);
				zmWart(stack, liczba);
			}
			else{
				push(pob, stack);
				wypiszL1(stack);
				pop(stack, pob);
				switch (pob[0]) {
				case '+':
					liczba = popint(stack);
					liczba += popint(stack);
					push(czyint,stack);
					zmWart(stack, liczba);
					break;
				case '-':
					liczba = 0;
					liczba -= popint(stack);
					liczba += popint(stack);
					push(czyint, stack);
					zmWart(stack, liczba);
					break;
				case '*':
					liczba = popint(stack);
					liczba *= popint(stack);
					push(czyint, stack);
					zmWart(stack, liczba);
					break;
				case '/':
					liczba = popint(stack);
					if (liczba == 0) {
						cout << "ERROR" << endl;
						brk = 1;
						break;
					}
					liczba = popint(stack)/liczba;
					push(czyint, stack);
					zmWart(stack, liczba);
					break;
				case 'I':
					int war[3];
					for (int i = 0; i < 3; i++)war[i] = popint(stack);
					push(czyint, stack);
					if(war[2]>0)zmWart(stack, war[1]);
					else zmWart(stack, war[0]);
					break;
				case 'N':
					liczba = popint(stack) * (-1);
					push(czyint, stack);
					zmWart(stack, liczba);
					break;
				case 'M':
					int mima = 0;
					if(stack!=nullptr) mima = popint(stack);
					for (int i = 0; i < (int(pob[3]) - 49); i++) {
						liczba = popint(stack);
						if (pob[1] == 'I' && liczba < mima) mima = liczba;
						if (pob[1] == 'A' && liczba > mima) mima = liczba;
					}
					push(czyint, stack);
					zmWart(stack, mima);
					break;
				}
				if (brk == 1)break;
			}
		}
		if(brk!=1)wypiszL1(stack);

		cout << endl;
		delListe(onp);
		delListe(stack);
		delListe(przec);
		brk = 0;
	}
	return 0;
}