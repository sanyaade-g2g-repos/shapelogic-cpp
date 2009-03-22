/*
 * BoostTest.cpp
 *
 * This file contains test of Boost
 *
 *  Created on: Oct 9, 2008
 *      Author: Sami Badawi
 */

#include <gtest/gtest.h>
#include <boost/lambda/lambda.hpp>

namespace {
using namespace std;
using namespace boost::lambda;


// Test the lambda expression in Boost
TEST(Boost, lambda) {
	const int N = 10;
	vector<double> V1(0);
	vector<double> V2(N);
	vector<double> V3(N);

	for (int i=0; i<N; i++) {
		V1.push_back(i);
	}
	fill(V2.begin(), V2.end(), 440);
	transform(V1.begin(), V1.end(), V2.begin(), V3.begin(),_1 + _2);
	//	transform(V1.begin(), V1.end(), V2.begin(), V3.begin(),plus<double>());
	EXPECT_EQ(0, V1[0]);
	EXPECT_EQ(440, V2[0]);
	EXPECT_EQ(440, V3[0]);
	EXPECT_EQ(N - 1 + 440, V3[N-1]);
}

}
