#include "catch.hpp"
#include "cmm/optional.hpp"


struct report {
};

class test_class {
public:
    test_class(report& r)
        : r{r}
    { }

private:
    report& r;
};


TEST_CASE("cmm::optional<T>")
{
    SECTION("cmm::optional<int>")
    {
        cmm::optional<int> o;

        REQUIRE(o.is_valid() == false);
        REQUIRE(bool(o) == false);

        o = cmm::optional<int>{128};

        REQUIRE(o.is_valid() == true);
        REQUIRE(bool(o) == true);
        REQUIRE(o.value() == 128);
    }
}
