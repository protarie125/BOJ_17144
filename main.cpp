#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;

int r, c, t;
vvi room;
int cltop, clbtm;
int ans;

void spr() {
	auto cpy = vvi{ room };
	for (auto i = 0; i < r; ++i) {
		for (auto j = 0; j < c; ++j) {
			if (4 < room[i][j]) {
				const auto& sam = room[i][j] / 5;

				if (0 <= i - 1) {
					if (-1 != room[i - 1][j]) {
						cpy[i - 1][j] += sam;
						cpy[i][j] -= sam;
					}
				}

				if (0 <= j - 1) {
					if (-1 != room[i][j - 1]) {
						cpy[i][j - 1] += sam;
						cpy[i][j] -= sam;
					}
				}

				if (i + 1 < r) {
					if (-1 != room[i + 1][j]) {
						cpy[i + 1][j] += sam;
						cpy[i][j] -= sam;
					}
				}

				if (j + 1 < c) {
					if (-1 != room[i][j + 1]) {
						cpy[i][j + 1] += sam;
						cpy[i][j] -= sam;
					}
				}
			}
		}
	}

	room = cpy;
}

void move() {
	// top
	// go down
	for (auto i = cltop - 1; 0 < i; --i) {
		room[i][0] = room[i - 1][0];
	}
	// go left
	for (auto j = 0; j < c - 1; ++j) {
		room[0][j] = room[0][j + 1];
	}
	// go up
	for (auto i = 0; i < cltop; ++i) {
		room[i][c - 1] = room[i + 1][c - 1];
	}
	// go right
	for (auto j = c - 1; 1 < j; --j) {
		room[cltop][j] = room[cltop][j - 1];
	}
	room[cltop][1] = 0;

	// btm
	// go up
	for (auto i = clbtm + 1; i < r - 1; ++i) {
		room[i][0] = room[i + 1][0];
	}
	// go left
	for (auto j = 0; j < c - 1; ++j) {
		room[r - 1][j] = room[r - 1][j + 1];
	}
	// go down
	for (auto i = r - 1; clbtm < i; --i) {
		room[i][c - 1] = room[i - 1][c - 1];
	}
	// go right
	for (auto j = c - 1; 1 < j; --j) {
		room[clbtm][j] = room[clbtm][j - 1];
	}
	room[clbtm][1] = 0;
}

void countUp() {
	ans = 0;
	for (auto i = 0; i < r; ++i) {
		for (auto j = 0; j < c; ++j) {
			if (0 < room[i][j]) {
				ans += room[i][j];
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> r >> c >> t;
	room = vvi(r, vi(c));
	cltop = -1;
	for (auto i = 0; i < r; ++i) {
		for (auto j = 0; j < c; ++j) {
			cin >> room[i][j];
			if (-1 == room[i][j]) {
				if (-1 == cltop) {
					cltop = i;
				}
				else {
					clbtm = i;
				}
			}
		}
	}

	for (auto i = 0; i < t; ++i) {
		spr();
		move();
	}

	countUp();
	cout << ans;

	return 0;
}