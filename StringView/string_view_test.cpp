#define CATCH_CONFIG_MAIN

#include <catch.hpp>

#include "string_view.h"
#include "string_view.h" // check include guards

SCENARIO("StringView Constructors", "[StringView]") {
  SECTION("Default constructor") {
    StringView sv;
    CHECK(sv.Data() == nullptr);
  }

  SECTION("Constructor From const char*") {
    const char *cstyle = "very_very_long_string_here";
    StringView sv(cstyle);

    CHECK(cstyle == sv.Data());
    CHECK(std::strlen(cstyle) == sv.Size());
  }

  SECTION("Constructor From const char* and size") {
    const char *cstyle = "very_very_long_string_here";
    StringView sv(cstyle, 26);

    CHECK(cstyle == sv.Data());
    CHECK(std::strlen(cstyle) == sv.Size());
  }
}

SCENARIO("Element access", "[StringView]") {
  const char *cstyle = "very_very_long_string_here";
  StringView sv(cstyle);
  StringView empty_sv;

  SECTION("Operator []") {
    CHECK(sv[5] == 'v');
  }

  SECTION("At()") {
    CHECK(sv.At(0) == 'v');
    CHECK(sv.At(6) == 'e');
    CHECK_THROWS_AS(sv.At(28), StringViewOutOfRange);
    CHECK_THROWS_AS(empty_sv.At(0), StringViewOutOfRange);
  }

  SECTION("Front() and Back()") {
    CHECK(sv.Front() == 'v');
    CHECK(sv.Back() == 'e');
  }

  SECTION("Data") {
    CHECK(sv.Data() == cstyle);
    CHECK(empty_sv.Data() == nullptr);
  }
}

SCENARIO("Capacity", "[StringView]") {
  const char *cstyle = "very_very_long_string_here";
  StringView sv(cstyle);
  StringView empty_sv;

  CHECK(sv.Size() == 26);
  CHECK(sv.Length() == 26);
  CHECK(!sv.Empty());
  CHECK(empty_sv.Empty());
}

SCENARIO("Methods", "[StringView]") {
  const char *cstyle = "very_very_long_string_here";
  StringView sv(cstyle);
  StringView empty_sv;

  SECTION("Swap") {
    sv.Swap(empty_sv);

    CHECK(sv.Data() == nullptr);
    CHECK(empty_sv.Data() == cstyle);
  }

  SECTION("RemovePrefix") {
    sv.RemovePrefix(2);

    CHECK(sv.Front() == 'r');
  }

  SECTION("RemoveSuffix") {
    sv.RemovePrefix(2);

    CHECK(sv.Back() == 'e');
  }

  SECTION("SubStr") {
    const char *c_str = "ABCDEF";
    StringView alphabet(c_str);
    std::vector<std::string> results{"ABCDEF", "BCDEF", "CDE", "EF"};

    using Catch::Matchers::Equals;

    CHECK_THAT(std::string(alphabet.Substr(0).Data()), Equals(results[0]));
    CHECK_THAT(std::string(alphabet.Substr(1).Data()), Equals(results[1]));
    CHECK_THAT(std::string(alphabet.Substr(2, 3).Data(), 3), Equals(results[2]));
    CHECK_THAT(std::string(alphabet.Substr(4, 42).Data()), Equals(results[3]));

    CHECK_THROWS_AS(alphabet.Substr(14, 42), StringViewOutOfRange);
  }
}
