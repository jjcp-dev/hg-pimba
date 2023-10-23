#include <type_traits>
#include "catch.hpp"
#include "lgf/internal/handle_owner.hpp"


class handle {
public:
    using id_type = int;

    id_type m_id;
    bool    destroyed = false;

    handle() = default;

    LGF_HANDLE_OWNER(handle);

    void destroy()
    {
        destroyed = true;
    }
};


TEST_CASE("LGF_HANDLE_OWNER")
{
    REQUIRE(std::is_copy_constructible<handle>::value == false);
    REQUIRE(std::is_move_constructible<handle>::value == true);
    REQUIRE(std::is_copy_assignable<handle>::value == false);
    REQUIRE(std::is_move_assignable<handle>::value == true);

    SECTION("move assignment")
    {
        handle h0, h1;

        h0.m_id = 100;
        h1.m_id = 200;

        REQUIRE(h0.destroyed == false);
        REQUIRE(h1.destroyed == false);

        h0 = std::move(h1);

        REQUIRE(h1.m_id == 0);
        REQUIRE(h1.destroyed == false);

        REQUIRE(h0.m_id == 200);
        REQUIRE(h0.destroyed == true);
    }

    SECTION("move construction")
    {
        handle h0;

        h0.m_id = 100;

        REQUIRE(h0.destroyed == false);

        handle h1{std::move(h0)};

        REQUIRE(h0.m_id == 0);
        REQUIRE(h0.destroyed == false);

        REQUIRE(h1.m_id == 100);
        REQUIRE(h1.destroyed == false);
    }
}
