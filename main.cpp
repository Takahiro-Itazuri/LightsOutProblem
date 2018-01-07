#include<iostream>
#include<string>

using namespace std;

int M, N;
bool* LO;
bool** options;
bool* comb;
int min = 10 * 10 + 1;

// ���a�ɑ΂��đ���b���s��
void toggle(bool* a, bool* b) {
	for (int i = 0; i < M * N; i++) {
		if (b[i] == true) a[i] = !(a[i]);
	}
}

// ���a��\��
void show(bool* a) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if(a[i * N + j]) cout << 'o';
			else cout << '.';
		}
		cout << endl;
	}
}

// �N���A����
bool clear(bool* a) {
	for (int i = 0; i < M * N; i++) {
		if (a[i] == true) return false;
	}
	return true;
}

// �[���D��T���őg�ݍ��킹�̑S�T��
void search(int count, bool bUse) {
	if (count == -1) { // ������
		comb = new bool[M * N];
		for (int i = 0; i < M * N; i++) {
			comb[i] = false;
		}

		search(count + 1, true);
		search(count + 1, false);
	}
	else if (count == M * N - 1) { // �I������
		comb[count] = bUse;

		// ���菈�� ================
		// ������
		bool* check = new bool[M * N];
		for (int i = 0; i < M * N; i++) {
			check[i] = LO[i];
		}

		// ����
		for (int i = 0; i < M * N; i++) {
			if (comb[i]) {
				toggle(check, options[i]);
			}
		}
		
		// ����
		if (clear(check)) { // �N���A�������̂݉����o��
			int c = 0;
			for (int i = 0; i < M * N; i++) {
				if (comb[i]) c++;
			}

			if (min > c) min = c;

			//�ǂ�ȃv���Z�X�ŃN���A�������̏o��
			//cout << "Number: " << c << "=====" << endl;
			//for (int i = 0; i < M * N; i++) {
			//	check[i] = LO[i];
			//}

			//int numOperation = 0;
			//for (int i = 0; i < M * N; i++) {
			//	if (comb[i]) {
			//		numOperation++;
			//		cout << numOperation << "��ڂ̑���" << endl;
			//		toggle(check, options[i]);
			//		show(check);
			//	}
			//}
		}

		// �������J��
		delete[] check;
		return;
	}
	else {
		comb[count] = bUse;
		if (bUse) {
			search(count + 1, true);
			search(count + 1, false);
		}
		else {
			search(count + 1, true);
			search(count + 1, false);
		}
	}
}

int main() {
	cin >> M >> N;
	cin.ignore();

	// ������
	LO = new bool[M * N];
	options = new bool*[M * N];
	for (int i = 0; i < M; i++) {
		string str;
		getline(cin, str);

		for (int j = 0; j < N; j++) {
			if (str[j] == 'o') LO[i * N + j] = true;
			else LO[i * N + j] = false;

			options[i * N + j] = new bool[M * N];
			bool* option = options[i * N + j];
			for (int _i = 0; _i < M; _i++) {
				for (int _j = 0; _j < N; _j++) {
					option[_i * N + _j] = false;
				}
			}

			option[i * N + j] = true;

			bool left = ((j - 1) >= 0), right = ((j + 1) < N), up = ((i - 1) >= 0), down = ((i + 1) < M);
			if (left) option[i * N + (j - 1)] = true;
			if (right) option[i * N + (j + 1)] = true;
			if (up) option[(i - 1) * N + j] = true;
			if (down) option[(i + 1) * N + j] = true;
		}
	}

	// �T��
	search(-1, true);

	// �������J��
	for (int i = 0; i < M * N; ++i) {
		delete[] options[i];
	}
	delete[] options;
	delete[] LO;

	if (min == 10 * 10 + 1) cout << -1 << endl;
	else cout << min << endl;

	return 0;
}