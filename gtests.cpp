#include <iostream>
#include "UrlParser.h"
#include "gtest/gtest.h"

TEST(UrlParserTest, ParseUrl) {
    UrlParser parser("http://example.com/path?query#fragment");

    EXPECT_EQ(parser.getScheme(), "http");
    EXPECT_EQ(parser.getLogin(), "");
    EXPECT_EQ(parser.getPassword(), "");
    EXPECT_EQ(parser.getHost(), "example.com");
    EXPECT_EQ(parser.getPort(), "");
    EXPECT_EQ(parser.getPath(), "/path");
    EXPECT_EQ(parser.getQuery(), "query");
    EXPECT_EQ(parser.getFragment(), "fragment");
}

TEST(UrlParserTest, ParseUrlWithPort) {
    UrlParser parser("http://example.com:8080/path?query#fragment");

    EXPECT_EQ(parser.getScheme(), "http");
    EXPECT_EQ(parser.getLogin(), "");
    EXPECT_EQ(parser.getPassword(), "");
    EXPECT_EQ(parser.getHost(), "example.com");
    EXPECT_EQ(parser.getPort(), "8080");
    EXPECT_EQ(parser.getPath(), "/path");
    EXPECT_EQ(parser.getQuery(), "query");
    EXPECT_EQ(parser.getFragment(), "fragment");
}

TEST(UrlParserTest, ParseUrl_Wiki) {
    UrlParser parser("https://ru.wikipedia.org/wiki/URL");

    EXPECT_EQ(parser.getScheme(), "https");
    EXPECT_EQ(parser.getLogin(), "");
    EXPECT_EQ(parser.getPassword(), "");
    EXPECT_EQ(parser.getHost(), "ru.wikipedia.org");
    EXPECT_EQ(parser.getPort(), "");
    EXPECT_EQ(parser.getPath(), "/wiki/URL");
    EXPECT_EQ(parser.getQuery(), "");
    EXPECT_EQ(parser.getFragment(), "");
}

TEST(UrlParserTest, ParseUrlFull) {
    UrlParser parser("http://login:password@example.com:8080/path?query#fragment");

    EXPECT_EQ(parser.getScheme(), "http");
    EXPECT_EQ(parser.getLogin(), "login");
    EXPECT_EQ(parser.getPassword(), "password");
    EXPECT_EQ(parser.getHost(), "example.com");
    EXPECT_EQ(parser.getPort(), "8080");
    EXPECT_EQ(parser.getPath(), "/path");
    EXPECT_EQ(parser.getQuery(), "query");
    EXPECT_EQ(parser.getFragment(), "fragment");
}

TEST(UrlParserTest, ParseUrlSomeSite) {
    UrlParser parser("https://marketplace.visualstudio.com/items?itemName=twxs.cmake");

    EXPECT_EQ(parser.getScheme(), "https");
    EXPECT_EQ(parser.getLogin(), "");
    EXPECT_EQ(parser.getPassword(), "");
    EXPECT_EQ(parser.getHost(), "marketplace.visualstudio.com");
    EXPECT_EQ(parser.getPort(), "");
    EXPECT_EQ(parser.getPath(), "/items");
    EXPECT_EQ(parser.getQuery(), "itemName=twxs.cmake");
    EXPECT_EQ(parser.getFragment(), "");
}

TEST(UrlParserTest, ParseUrlEmptyScheme) {
    try {
        UrlParser parser("://login:password@example.com:8080/path?query#fragment");
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Invalid URL: Missing scheme"));
    }
    catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST(UrlParserTest, ParseUrlYandexSlash) {
    UrlParser parser("https://ya.ru/");

    EXPECT_EQ(parser.getScheme(), "https");
    EXPECT_EQ(parser.getHost(), "ya.ru");
    EXPECT_EQ(parser.getPath(), "/");
}

TEST(UrlParserTest, ParseUrlYandex) {
    try {
        UrlParser parser("https://ya.ru");
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Invalid URL: Missing path"));
    }
    catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST(UrlParserTest, ParseUrlOnlyScheme) {
    try {
        UrlParser parser("https://");
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Invalid URL: Missing host"));
    }
    catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

