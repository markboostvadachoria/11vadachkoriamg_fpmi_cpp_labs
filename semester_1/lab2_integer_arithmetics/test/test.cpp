#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include <stdexcept>

struct Triple { 
    double x{-1};
    double y{-1};
    double z{-1}; 
};

std::vector<Triple> findPythagoreanTriples(int n);

TEST(PythagoreanTriplesTest, CheckSize) {
    EXPECT_EQ(findPythagoreanTriples(0).size(), 0);
    EXPECT_EQ(findPythagoreanTriples(1).size(), 0);
    EXPECT_EQ(findPythagoreanTriples(2).size(), 0);
    EXPECT_EQ(findPythagoreanTriples(3).size(), 0);
    EXPECT_EQ(findPythagoreanTriples(4).size(), 0);
    
    EXPECT_EQ(findPythagoreanTriples(5).size(), 1);

    EXPECT_EQ(findPythagoreanTriples(10).size(), 2);
    EXPECT_EQ(findPythagoreanTriples(13).size(), 3);
}

TEST(PythagoreanTriplesTest, TriplesAreInt) {
    std::vector<Triple> triples = findPythagoreanTriples(20);
    
    for (const auto t : triples) {
        EXPECT_EQ(t.x - floor(t.x), 0);
        EXPECT_EQ(t.y - floor(t.y), 0);
        EXPECT_EQ(t.z - floor(t.z), 0);

        EXPECT_EQ(t.x, static_cast<int>(t.x));
        EXPECT_EQ(t.y, static_cast<int>(t.y));
        EXPECT_EQ(t.z, static_cast<int>(t.z));
    }
}


TEST(PythagoreanTriplesTest, EdgeCases) {   
    EXPECT_THROW(findPythagoreanTriples(-1), std::invalid_argument);
   
    EXPECT_EQ(findPythagoreanTriples(0).size(), 0);
    for (int i = 1; i <= 4; i++) {
        EXPECT_EQ(findPythagoreanTriples(i).size(), 0);
    }
}

TEST(PythagoreanTriplesTest, SimpleTriples) {   
    std::vector<Triple> rightTriple = {
        {3, 4, 5},
        {6, 8, 10},
        {5, 12, 13},
        {9, 12, 15},
        {8, 15, 17},
        {12, 16, 20}
    };
    
    std::vector<Triple> triples = findPythagoreanTriples(20);
    
    EXPECT_EQ(triples.size(), rightTriple.size());
    
    for (size_t i = 0; i < triples.size(); i++) {
        const auto t = triples[i];
        const auto known = rightTriple[i];
        
        EXPECT_DOUBLE_EQ(t.x, known.x);
        EXPECT_DOUBLE_EQ(t.y, known.y);
        EXPECT_DOUBLE_EQ(t.z, known.z);
     }
}


