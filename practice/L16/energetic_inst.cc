template <int N> struct Danger {
    typedef char block[N];
};

template <typename T, int N>
struct Tricky {
    void test_lazyness() {
        Danger<N> no_boom_yet;
    }
};

#ifdef EXPLICIT_ENERGETIC_INST
template struct Tricky<int, -2>;
#endif
#ifdef SPECIALIZATION
template<> struct Tricky<int, -2> {};
#endif

int main() {
    Tricky<int, -2> ok; // ok (if I is commented)
    // ok.test_lazyness(); // error if uncomment
}


