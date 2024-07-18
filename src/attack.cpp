#define MSGS 2

#include "shuffle.cpp"

void print_messages(vector < vector < params::poly_q >> m,
		vector < vector < params::poly_q >> _m) {
	for (int i = 0; i < MSGS; i++) {
		for (int j = 0; j < SIZE; j++) {
			std::cout << "#### m[" << i << "][" << j << "]: " << m[i][j] << std::endl;
		}
	}

	for (int i = 0; i < MSGS; i++) {
		for (int j = 0; j < SIZE; j++) {
			std::cout << "#### _m[" << i << "][" << j << "]: " << _m[i][j] << std::endl;
		}
	}
}

void attack() {
	comkey_t key;
	commit_t com[MSGS];
	vector < vector < params::poly_q >> m(MSGS), _m(MSGS);
	vector < params::poly_q > r[MSGS];

	// Generate original messages and commitments
	bdlop_keygen(key);
	for (int i = 0; i < MSGS; i++) {
		m[i].resize(SIZE);
		for (int j = 0; j < SIZE; j++) {
			m[i][j] = nfl::ZO_dist();
		}
		r[i].resize(WIDTH);
		bdlop_sample_rand(r[i]);
		bdlop_commit(com[i], m[i], key, r[i]);
	}

	// Copy the original messages
	for (int i = 0; i < MSGS; i++) {
		_m[i].resize(SIZE);
		for (int j = 0; j < SIZE; j++) {
			_m[i][j] = m[i][j];
		}
	}

	// Swap first CRT component of the first two messages
	for (int j=0; j < SIZE; j++) {
		_m[0][j].ntt_pow_phi();
		_m[1][j].ntt_pow_phi();

		auto data0 = _m[0][j].data();
		auto data1 = _m[1][j].data();
		std::swap(data0[0], data1[0]);

		_m[0][j].invntt_pow_invphi();
		_m[1][j].invntt_pow_invphi();
	}

    /*
        The polynomials in m have coefficients in {-1, 0, 1}, whereas 
        the modified polynomials in _m will generally have large
        coefficients. This is an easy-to-check fact that shows that
        the vectors m and _m are not related by a shuffle.
    */
	// print_messages(m, _m);

	TEST_ONCE("attack works") {
		TEST_ASSERT(run(com, m, _m, key, r) == 1, end);
	} TEST_END;

  end:
	return;
}

int main() {
    printf("\n** Attack against the shuffle proof:\n\n");
	attack();
}