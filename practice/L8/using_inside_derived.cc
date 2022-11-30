#include <iostream>
struct Matrix {
	virtual void pow(double x) {std::cout << "1" << std::endl; }
    virtual void pow(int x) {std::cout << "2" << std::endl; }
};
 
struct SparseMatrix : public Matrix {
	using Matrix::pow; // затаскиваем имена из скопа Matrix
    void pow(int x) override {std::cout << "3" << std::endl; }
};
 
int main() {
#ifdef BASE
	Matrix *m = new SparseMatrix{};
#else
	SparseMatrix *m = new SparseMatrix{};
#endif
    m->pow(1.5);
}
