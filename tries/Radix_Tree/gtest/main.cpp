#include <string>
#include "radix_tree.cpp"
#include "gtest/gtest.h"

class RadixTest : public testing::Test {
protected:
  virtual void TearDown() { t.clear(); }

  RadixTree::radix_tree<int, 256> t;
}; // class

TEST_F(RadixTest, SizeOfAnEmptyObjectIsZero) {
  EXPECT_EQ(0, t.size()) << "Size for an empty object should be always zero";
}

TEST_F(RadixTest, SizeOfAnObjectWithOneElement) {
  const std::string key = "key";
  const int value = 42;
  t.insert(key, value);
  EXPECT_EQ(1, t.size())
      << "Size for an object with one element should be one ";
}

TEST_F(RadixTest, FindANotInsertedKey) {
  const std::string no_key = "no";
  EXPECT_EQ(0, t.find(no_key)) << "Find a key that is not in the object "
                                  "has to return the entry with the "
                                  "default contructor of the template";
}

TEST_F(RadixTest, FindAnInsertedKey) {
  const std::string key = "hi";
  const int value = 42;
  t.insert(key, value);
  EXPECT_EQ(42, t.find(key)) << "After inserting an entry in the object. It "
                                "should be able to be retrieved";
}

TEST_F(RadixTest, CleanAnObjectWithOneElement) {
  const std::string key = "key";
  const int value = 42;
  t.insert(key, value);
  t.clear();
  EXPECT_EQ(0, t.size()) << "The size of an object after clear should be zero";
}

TEST_F(RadixTest, FindAKeyAfterObjectHasBeenCleared) {
  const std::string key = "key";
  const int value = 42;
  t.insert(key, value);
  t.clear();
  EXPECT_EQ(0, t.find(key)) << "The result of find for an inserter key after "
                               "the object has been cleared should be zero";
}

TEST_F(RadixTest, EraseInsertedKey) {
	const std::string key = "key";
	const int value = 42;
	t.insert(key, value);
	t.erase(key);
	EXPECT_EQ(0, t.find(key)) << "After removing an inserted entry in the"
		"object it should return the entry with the default constructor"
		"of the template";
}

TEST_F(RadixTest, EraseNonInsertedKey) {
	const std::string key = "key";
	t.erase(key);
	EXPECT_EQ(0, t.size()) << "Removing a non inserted entry should not"
		"affect at all to the state of the object";
}

TEST_F(RadixTest, ContainsAnInsertedKey) {
	const std::string key = "key";
	const int value = 42;
	t.insert(key, value);
	EXPECT_TRUE(t.contains(key)) << "The object should return true when"
		"it contains the entry";
}

TEST_F(RadixTest, ContainsANonInsertedKey) {
	const std::string key = "key";
	EXPECT_FALSE(t.contains(key)) << "The object should return false"
		"when it does not contain the entry";
}

TEST_F(RadixTest, LongestCommonPathOfAnEmptyObject) {
	EXPECT_EQ("", t.lcp()) << "The longest common path of an empty object"
		"should be the empty string";
}

TEST_F(RadixTest, LongestCommonPathOfThreeObjects) {
  std::string hello = "Hello", world = "World", wololo = "Wololo";

  t.insert(hello, 1);
  t.insert(world, 2);
  t.insert(wololo, 3);
  EXPECT_EQ("", t.lcp()) << "This should be ''";
}

TEST_F(RadixTest, LongestCommonPathOfTwoObjects) {
	std::string world = "World", wololo = "Wololo";
	t.insert(world, 2);
	t.insert(wololo, 3);
	EXPECT_EQ("Wo", t.lcp()) << "This should be 'Wo'";
}

TEST_F(RadixTest, LongestCommonPathOfTwoObjectAfterRemovingOne) {
	std::string hello = "Hello", world = "World", wololo = "Wololo";
	t.insert(hello, 1);
	t.insert(world, 2);
	t.insert(wololo, 3);
	t.erase(hello);
	EXPECT_EQ("Wo", t.lcp()) << "This should be 'Wo'";
}

TEST_F(RadixTest, LongestCommonPathAfterClear) {
	std::string hello = "Hello";
	t.insert(hello, 1);
	t.clear();
	EXPECT_EQ("", t.lcp()) << "This should be ''";
}

TEST_F(RadixTest, LongestCommonPathOfOneObject) {
	std::string hello = "Hello";
	t.insert(hello, 1);
	EXPECT_EQ("Hello", t.lcp()) << "This should be 'Hello'";
}

TEST_F(RadixTest, LongestCommonPathOfOneObjectAfterClear) {
	std::string hello = "Hello";
	t.insert(hello, 1);
	t.clear();
	t.insert(hello, 1);
	EXPECT_EQ("Hello", t.lcp()) << "This should be 'Hello'";
}

TEST_F(RadixTest, GetKeysWithNoObjects) {
	EXPECT_EQ(0, t.keys().size()) << "The size of the vector should be 0";
}

TEST_F(RadixTest, GetKeysWithOneObjects) {
	std::string hello = "Hello";
	t.insert(hello, 1);
	EXPECT_EQ(1, t.keys().size()) << "The size of the vector should be 1";
}

TEST_F(RadixTest, GetKeysWithTwoObjects) {
	std::string world = "World", wololo = "Wololo";
	t.insert(world, 2);
	t.insert(wololo, 3);
	EXPECT_EQ(2, t.keys().size()) << "The size of the vector should be 2";
}

TEST_F(RadixTest, GetKeysWithNoObjectsAfterClear) {
	std::string hello = "Hello";
	t.insert(hello, 1);
	t.clear();
	EXPECT_EQ(0, t.keys().size()) << "The size of the vector should be 0";
}

TEST_F(RadixTest, GetKeysWithOneObjectsAfterClear) {
	std::string hello = "Hello";
	t.insert(hello, 1);
	t.clear();
	t.insert(hello, 1);
	EXPECT_EQ(1, t.keys().size()) << "The size of the vector should be 1";
}

TEST_F(RadixTest, MethodGetKeyWithPrefixOfEmptyObject) {
	EXPECT_EQ(0, t.keys("").size()) << "The size of the vector should be 0";
}

TEST_F(RadixTest, MethodGetKeyWithPrefixOfSevenObjects1) {
  std::string hello = "Hello", world = "World", wololo = "Wololo", he = "He",
              kthulu = "Kthulu", no = "No", hes = "Hes";
  t.insert(hello, 1);
  t.insert(world, 2);
  t.insert(wololo, 3);
  t.insert(he, 4);
  t.insert(kthulu, 5);
  t.insert(no, 6);
  t.insert(hes, 7);
  EXPECT_EQ(1, t.keys("Hel").size()) << "This should be 1";
}

TEST_F(RadixTest, MethodGetKeyWithPrefixOfSevenObjects2) {
  std::string hello = "Hello", world = "World", wololo = "Wololo", he = "He",
              kthulu = "Kthulu", no = "No", hes = "Hes";
  t.insert(hello, 1);
  t.insert(world, 2);
  t.insert(wololo, 3);
  t.insert(he, 4);
  t.insert(kthulu, 5);
  t.insert(no, 6);
  t.insert(hes, 7);
  EXPECT_EQ(1, t.keys("N").size()) << "This should be 1";
}

TEST_F(RadixTest, MethodGetKeyWithPrefixOfSevenObjects3) {
  std::string hello = "Hello", world = "World", wololo = "Wololo", he = "He",
              kthulu = "Kthulu", no = "No", hes = "Hes";
  t.insert(hello, 1);
  t.insert(world, 2);
  t.insert(wololo, 3);
  t.insert(he, 4);
  t.insert(kthulu, 5);
  t.insert(no, 6);
  t.insert(hes, 7);
  EXPECT_EQ(1, t.keys("No").size()) << "This should be 1";
}

TEST_F(RadixTest, MethodGetKeyWithPrefixOfSevenObjects4) {
  std::string hello = "Hello", world = "World", wololo = "Wololo", he = "He",
              kthulu = "Kthulu", no = "No", hes = "Hes";
  t.insert(hello, 1);
  t.insert(world, 2);
  t.insert(wololo, 3);
  t.insert(he, 4);
  t.insert(kthulu, 5);
  t.insert(no, 6);
  t.insert(hes, 7);
  EXPECT_EQ(0, t.keys("Nos").size()) << "This should be 0";
}

TEST_F(RadixTest, MethodGetKeyWithPrefixOfSevenObjects5) {
  std::string hello = "Hello", world = "World", wololo = "Wololo", he = "He",
              kthulu = "Kthulu", no = "No", hes = "Hes";
  t.insert(hello, 1);
  t.insert(world, 2);
  t.insert(wololo, 3);
  t.insert(he, 4);
  t.insert(kthulu, 5);
  t.insert(no, 6);
  t.insert(hes, 7);
  EXPECT_EQ(2, t.keys("W").size()) << "This should be 2";
}

TEST_F(RadixTest, MethodGetKeyWithPrefixOfSevenObjects6) {
  std::string hello = "Hello", world = "World", wololo = "Wololo", he = "He",
              kthulu = "Kthulu", no = "No", hes = "Hes";
  t.insert(hello, 1);
  t.insert(world, 2);
  t.insert(wololo, 3);
  t.insert(he, 4);
  t.insert(kthulu, 5);
  t.insert(no, 6);
  t.insert(hes, 7);
  EXPECT_EQ(2, t.keys("Wo").size()) << "This should be 2";
}

TEST_F(RadixTest, MethodGetKeyWithPrefixOfSevenObjects7) {
  std::string hello = "Hello", world = "World", wololo = "Wololo", he = "He",
              kthulu = "Kthulu", no = "No", hes = "Hes";
  t.insert(hello, 1);
  t.insert(world, 2);
  t.insert(wololo, 3);
  t.insert(he, 4);
  t.insert(kthulu, 5);
  t.insert(no, 6);
  t.insert(hes, 7);
  EXPECT_EQ(0, t.keys("Wou").size()) << "This should be 0";
}

TEST_F(RadixTest, EmptyStringParameterFind) {
	EXPECT_EQ(0, t.find("")) << "Find from an empty string should be ALWAYS 0";
}

TEST_F(RadixTest, EmptyStringParameterInsert) {
	t.insert("", 1);
	EXPECT_EQ(0, t.size()) << "Insert an empty string should never do anything";
}

TEST_F(RadixTest, EmptyStringParameterErase) {
	std::string hello = "Hello";
	t.insert(hello, 1);
	t.erase("");
	EXPECT_EQ(1, t.size()) << "Erase an empty string should never do anything";
}

TEST_F(RadixTest, EmptyStringParameterContains) {
	EXPECT_FALSE(t.contains("")) << "Contains from an empty string should be 0 ALWAYS";
}

TEST_F(RadixTest, MethodShow) {
	std::string hello = "Hello", world = "World", wololo = "Wololo", he = "He",
		kthulu = "Kthulu", no = "No", hes = "Hes";
	t.insert(hello, 1);
	t.insert(world, 2);
	t.insert(he, 3);
	t.insert(kthulu, 4);
	t.insert(no, 5);
	t.insert(hes, 6);
	t.insert(wololo, 7);
	t.show();
	EXPECT_TRUE(true) << "This test is just to check that show method does not break";
}

TEST_F(RadixTest, LongTest) {
  std::string hello = "Hello", world = "World", wololo = "Wololo", he = "He",
              kthulu = "Kthulu", no = "No", hes = "Hes";

  t.insert(hello, 1);
  t.insert(world, 2);
  t.insert(wololo, 3);
  EXPECT_EQ(3, t.size()) << "This should be 3";
  EXPECT_EQ(1, t.find(hello)) << "This should be 1";
  EXPECT_EQ(2, t.find(world)) << "This should be 2";
  EXPECT_EQ(3, t.find(wololo)) << "This should be 3";

  // Checking before and after adding Kthulu. The prefix is new in the trie.
  EXPECT_EQ(0, t.find(kthulu)) << "This should be 0";
  t.insert(kthulu, 4);
  EXPECT_EQ(4, t.size()) << "This should be 4";
  EXPECT_EQ(4, t.find(kthulu)) << "This should be 4";

  // Checking before and after adding He. The prefix was alreay in the trie.
  EXPECT_EQ(0, t.find(he)) << "This should be 0";
  t.insert(he, 5);
  EXPECT_EQ(5, t.size()) << "This should be 5";
  EXPECT_EQ(5, t.find(he)) << "This should be 5";

  // Checking content that is not in the trie
  EXPECT_EQ(0, t.find(no)) << "This should be 0";
  EXPECT_EQ(0, t.find(hes)) << "This should be 0";

  // Getting some keys with prefix "He". Should be 2.
  std::vector<std::string> keys;
  keys = t.keys("He");
  EXPECT_EQ(2, keys.size()) << "This should be 2";
  EXPECT_EQ(he, keys[0]);
  EXPECT_EQ(hello, keys[1]);

  // Getting some keys with prefix "Hi". Should be none
  keys = t.keys("His");
  EXPECT_EQ(0, keys.size()) << "This should be 0";

  // Gettin some keys with prefix "H". Should be 2.
  keys = t.keys("H");
  EXPECT_EQ(2, keys.size()) << "This should be 2";
  EXPECT_EQ(he, keys[0]);
  EXPECT_EQ(hello, keys[1]);

  // Updating value of "He"
  EXPECT_EQ(5, t.find(he)) << "This should be 5";
  t.insert(he, 7);
  EXPECT_EQ(7, t.find(he)) << "This should be 7";
  EXPECT_EQ(5, t.size()) << "This should be 5";

  // Removing hello
  t.erase(hello);
  EXPECT_EQ(4, t.size()) << "This should be 4";
  keys = t.keys("He");
  EXPECT_EQ(1, keys.size()) << "This should be 1";
  EXPECT_EQ(he, keys[0]);
  EXPECT_EQ(0, t.find(hello)) << "This should be 0";
  // Removing hello again. Shoul not make any difference
  t.erase(hello);
  EXPECT_EQ(4, t.size()) << "This should be 4";
  keys = t.keys("He");
  EXPECT_EQ(1, keys.size()) << "This should be 1";
  EXPECT_EQ(he, keys[0]);
  EXPECT_EQ(0, t.find(hello)) << "This should be 0";
  // Re-adding hello again
  t.insert(hello, 1);
  EXPECT_EQ(5, t.size()) << "This should be 5";
  keys = t.keys("He");
  EXPECT_EQ(2, keys.size()) << "This should be 2";
  EXPECT_EQ(he, keys[0]);
  EXPECT_EQ(hello, keys[1]);
  EXPECT_EQ(1, t.find(hello)) << "This should be 1";

  // Removing he
  t.erase(he);
  EXPECT_EQ(4, t.size()) << "This should be 4";
  keys = t.keys("He");
  EXPECT_EQ(1, keys.size()) << "This should be 1";
  EXPECT_EQ(hello, keys[0]);
  EXPECT_EQ(0, t.find(he)) << "This should be 0";
  // Removing hello again. Shoul not make any difference
  t.erase(he);
  EXPECT_EQ(4, t.size()) << "This should be 4";
  keys = t.keys("He");
  EXPECT_EQ(1, keys.size()) << "This should be 1";
  EXPECT_EQ(hello, keys[0]);
  EXPECT_EQ(0, t.find(he)) << "This should be 0";
  // Re-adding hello again
  t.insert(he, 7);
  EXPECT_EQ(5, t.size()) << "This should be 5";
  keys = t.keys("He");
  EXPECT_EQ(2, keys.size()) << "This should be 2";
  EXPECT_EQ(he, keys[0]);
  EXPECT_EQ(hello, keys[1]);
  EXPECT_EQ(7, t.find(he)) << "This should be 7";

  // Finally removing hello
  t.erase(hello);
  EXPECT_EQ(4, t.size()) << "This should be 4";
  t.erase(he);
  EXPECT_EQ(3, t.size()) << "This should be 3";
  t.erase(hes);
  EXPECT_EQ(3, t.size()) << "This should be 3";
  t.erase(no);
  EXPECT_EQ(3, t.size()) << "This should be 3";
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
