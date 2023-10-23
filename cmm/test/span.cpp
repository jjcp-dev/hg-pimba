#include "catch.hpp"
#include "cmm/span.hpp"

#include <type_traits>
#include <vector>
#include <cstring>


TEST_CASE("cmm::span<T>")
{
    SECTION("empty span")
    {
        SECTION("default constructor")
        {
            cmm::span<double> s;

            REQUIRE(s.data() == nullptr);
            REQUIRE(s.size() == 0);
            REQUIRE(s.size_bytes() == 0);
            REQUIRE(s.begin() == s.end());
            REQUIRE(s.cbegin() == s.cend());
        }

        SECTION("from empty container")
        {
            std::vector<float> source;

            cmm::span<float> s{source};

            REQUIRE(s.data() == source.data());
            REQUIRE(s.size() == 0);
            REQUIRE(s.size_bytes() == 0);
            REQUIRE(s.begin() == s.end());
            REQUIRE(s.cbegin() == s.cend());
        }

        SECTION("from (ptr, size) pair")
        {
            float source = 0.0f;

            cmm::span<float> s{&source, 0};

            REQUIRE(s.data() == &source);
            REQUIRE(s.size() == 0);
            REQUIRE(s.size_bytes() == 0);
            REQUIRE(s.begin() == s.end());
            REQUIRE(s.cbegin() == s.cend());
        }
    }

    SECTION("one element span")
    {
        SECTION("from array")
        {
            int source[] = {128};

            cmm::span<int> s{source};

            REQUIRE(s.data() == source);
            REQUIRE(s.size() == 1);
            REQUIRE(s.size_bytes() == 1 * sizeof(int));

            REQUIRE(s.begin() != s.end());
            REQUIRE(s.cbegin() != s.cend());

            REQUIRE(s.end() - s.begin() == 1);
            REQUIRE(s.cend() - s.cbegin() == 1);

            REQUIRE(s[0] == 128);

            REQUIRE(std::equal(std::begin(s),
                               std::end(s),
                               std::begin(source)));
        }

        SECTION("from container")
        {
            std::vector<int> source({128});
            cmm::span<int> s{source};

            REQUIRE(s.data() == source.data());
            REQUIRE(s.size() == 1);
            REQUIRE(s.size_bytes() == 1 * sizeof(int));

            REQUIRE(s.begin() != s.end());
            REQUIRE(s.cbegin() != s.cend());

            REQUIRE(s.end() - s.begin() == 1);
            REQUIRE(s.cend() - s.cbegin() == 1);

            REQUIRE(s[0] == 128);

            REQUIRE(std::equal(std::begin(s),
                               std::end(s),
                               std::begin(source)));
        }

        SECTION("from (ptr, size) pair")
        {
            float source[] = {3.4f};
            cmm::span<float> s{source, 1};

            REQUIRE(s.data() == source);
            REQUIRE(s.size() == 1);
            REQUIRE(s.size_bytes() == 1 * sizeof(float));

            REQUIRE(s.begin() != s.end());
            REQUIRE(s.cbegin() != s.cend());

            REQUIRE(s.end() - s.begin() == 1);
            REQUIRE(s.cend() - s.cbegin() == 1);

            REQUIRE(s[0] == 3.4f);

            REQUIRE(std::equal(std::begin(s),
                               std::end(s),
                               std::begin(source)));
        }
    }

    SECTION("multiple elements")
    {
        SECTION("from array")
        {
            int source[] = {128, 256, 512};

            cmm::span<int> s{source};

            REQUIRE(s.data() == source);
            REQUIRE(s.size() == 3);
            REQUIRE(s.size_bytes() == 3 * sizeof(int));

            REQUIRE(s.begin() != s.end());
            REQUIRE(s.cbegin() != s.cend());

            REQUIRE(s.end() - s.begin() == 3);
            REQUIRE(s.cend() - s.cbegin() == 3);

            REQUIRE(s[0] == 128);
            REQUIRE(s[1] == 256);
            REQUIRE(s[2] == 512);

            REQUIRE(std::equal(std::begin(s),
                               std::end(s),
                               std::begin(source)));
        }

        SECTION("from container")
        {
            std::vector<float> source({1.0f, 2.0f, 3.0f});

            cmm::span<float> s{source};

            REQUIRE(s.data() == source.data());
            REQUIRE(s.size() == 3);
            REQUIRE(s.size_bytes() == 3 * sizeof(float));

            REQUIRE(s.begin() != s.end());
            REQUIRE(s.cbegin() != s.cend());

            REQUIRE(s.end() - s.begin() == 3);
            REQUIRE(s.cend() - s.cbegin() == 3);

            REQUIRE(s[0] == 1.0f);
            REQUIRE(s[1] == 2.0f);
            REQUIRE(s[2] == 3.0f);

            REQUIRE(std::equal(std::begin(s),
                               std::end(s),
                               std::begin(source)));
        }

        SECTION("from (ptr, size) pairs")
        {
            float source[] = {4.0f, 5.0f, 6.0f};

            cmm::span<float> s{source, 3};

            REQUIRE(s.data() == source);
            REQUIRE(s.size() == 3);
            REQUIRE(s.size_bytes() == 3 * sizeof(float));

            REQUIRE(s.begin() != s.end());
            REQUIRE(s.cbegin() != s.cend());

            REQUIRE(s.end() - s.begin() == 3);
            REQUIRE(s.cend() - s.cbegin() == 3);

            REQUIRE(s[0] == 4.0f);
            REQUIRE(s[1] == 5.0f);
            REQUIRE(s[2] == 6.0f);

            REQUIRE(std::equal(std::begin(s),
                               std::end(s),
                               std::begin(source)));
        }
    }

    SECTION("empty rspan")
    {
        REQUIRE(std::is_same<cmm::rspan, cmm::span<cmm::raw>>::value == true);

        SECTION("default constructor")
        {
            cmm::rspan s;

            REQUIRE(s.data() == nullptr);
            REQUIRE(s.size() == 0);
            REQUIRE(s.size_bytes() == 0);
            REQUIRE(s.begin() == s.end());
            REQUIRE(s.cbegin() == s.cend());
        }

        SECTION("from empty container")
        {
            std::vector<int> source;
            cmm::rspan s{source};

            REQUIRE((void*) s.data() == (void*) source.data());
            REQUIRE(s.size() == 0);
            REQUIRE(s.size_bytes() == 0);
            REQUIRE(s.begin() == s.end());
            REQUIRE(s.cbegin() == s.cend());
        }

        SECTION("from (ptr, size) pair")
        {
            float source = 0.0f;

            cmm::rspan s{&source, 0};

            REQUIRE((void*) s.data() == (void*) &source);
            REQUIRE(s.size() == 0);
            REQUIRE(s.size_bytes() == 0);
            REQUIRE(s.begin() == s.end());
            REQUIRE(s.cbegin() == s.cend());
        }
    }

    SECTION("one element rspan")
    {
        SECTION("from array")
        {
            int source[] = {128};

            cmm::rspan s{source};

            REQUIRE((void*) s.data() == (void*) source);
            REQUIRE(s.size() == 1 * sizeof(int));
            REQUIRE(s.size_bytes() == 1 * sizeof(int));

            REQUIRE(s.begin() != s.end());
            REQUIRE(s.cbegin() != s.cend());

            REQUIRE(s.end() - s.begin() == 1 * sizeof(int));
            REQUIRE(s.cend() - s.cbegin() == 1 * sizeof(int));

            REQUIRE(std::equal(std::begin(s),
                               std::end(s),
                               reinterpret_cast<cmm::byte*>(source)));

            REQUIRE(std::equal(std::cbegin(s),
                               std::cend(s),
                               reinterpret_cast<const cmm::byte*>(source)));

            for (auto i = 0; i < (int) sizeof(source); i++)
                REQUIRE(s[i] == reinterpret_cast<cmm::byte*>(source)[i]);
        }

        SECTION("from container")
        {
            std::vector<int> source({128});
            cmm::rspan s{source};

            REQUIRE((void*) s.data() == (void*) source.data());
            REQUIRE(s.size() == 1 * sizeof(int));
            REQUIRE(s.size_bytes() == 1 * sizeof(int));

            REQUIRE(s.begin() != s.end());
            REQUIRE(s.cbegin() != s.cend());

            REQUIRE(s.end() - s.begin() == 1 * sizeof(int));
            REQUIRE(s.cend() - s.cbegin() == 1 * sizeof(int));

            REQUIRE(std::equal(std::begin(s),
                               std::end(s),
                               reinterpret_cast<cmm::byte*>(source.data())));

            REQUIRE(std::equal(std::cbegin(s),
                               std::cend(s),
                               reinterpret_cast<const cmm::byte*>(source.data())));

            for (auto i = 0; i < static_cast<int>(sizeof(int) * source.size()); i++)
                REQUIRE(s[i] == reinterpret_cast<cmm::byte*>(source.data())[i]);
        }

        SECTION("from (ptr, size) pair")
        {
            float source[] = {3.4f};
            cmm::rspan s{source, sizeof(float)};

            REQUIRE((void*) s.data() == (void*) source);
            REQUIRE(s.size() == 1 * sizeof(float));
            REQUIRE(s.size_bytes() == 1 * sizeof(float));

            REQUIRE(s.begin() != s.end());
            REQUIRE(s.cbegin() != s.cend());

            REQUIRE(s.end() - s.begin() == 1 * sizeof(float));
            REQUIRE(s.cend() - s.cbegin() == 1 * sizeof(float));

            REQUIRE(std::equal(std::begin(s),
                               std::end(s),
                               reinterpret_cast<cmm::byte*>(&source)));

            REQUIRE(std::equal(std::cbegin(s),
                               std::cend(s),
                               reinterpret_cast<const cmm::byte*>(&source)));

            for (auto i = 0; i < static_cast<int>(sizeof(float)); i++)
                REQUIRE(s[i] == reinterpret_cast<cmm::byte*>(&source)[i]);
        }
    }

    SECTION("empty cspan")
    {
        REQUIRE(std::is_same<cmm::cspan, cmm::span<const cmm::raw>>::value == true);

        SECTION("default constructor")
        {
            cmm::cspan s;

            REQUIRE(s.data() == nullptr);
            REQUIRE(s.size() == 0);
            REQUIRE(s.size_bytes() == 0);
            REQUIRE(s.begin() == s.end());
            REQUIRE(s.cbegin() == s.cend());
        }

        SECTION("from empty container")
        {
            std::vector<int> source;
            cmm::cspan s{source};

            REQUIRE((void*) s.data() == (void*) source.data());
            REQUIRE(s.size() == 0);
            REQUIRE(s.size_bytes() == 0);
            REQUIRE(s.begin() == s.end());
            REQUIRE(s.cbegin() == s.cend());
        }

        SECTION("from (ptr, size) pair")
        {
            float source = 0.0f;

            cmm::cspan s{&source, 0};

            REQUIRE((void*) s.data() == (void*) &source);
            REQUIRE(s.size() == 0);
            REQUIRE(s.size_bytes() == 0);
            REQUIRE(s.begin() == s.end());
            REQUIRE(s.cbegin() == s.cend());
        }
    }

    SECTION("one element cspan")
    {
        SECTION("from array")
        {
            int source[] = {128};

            cmm::cspan s{source};

            REQUIRE((void*) s.data() == (void*) source);
            REQUIRE(s.size() == 1 * sizeof(int));
            REQUIRE(s.size_bytes() == 1 * sizeof(int));

            REQUIRE(s.begin() != s.end());
            REQUIRE(s.cbegin() != s.cend());

            REQUIRE(s.end() - s.begin() == 1 * sizeof(int));
            REQUIRE(s.cend() - s.cbegin() == 1 * sizeof(int));

            REQUIRE(std::equal(std::begin(s),
                               std::end(s),
                               reinterpret_cast<cmm::byte*>(source)));

            REQUIRE(std::equal(std::cbegin(s),
                               std::cend(s),
                               reinterpret_cast<const cmm::byte*>(source)));

            for (auto i = 0; i < (int) sizeof(source); i++)
                REQUIRE(s[i] == reinterpret_cast<cmm::byte*>(source)[i]);
        }

        SECTION("from container")
        {
            std::vector<int> source({128});
            cmm::cspan s{source};

            REQUIRE((void*) s.data() == (void*) source.data());
            REQUIRE(s.size() == 1 * sizeof(int));
            REQUIRE(s.size_bytes() == 1 * sizeof(int));

            REQUIRE(s.begin() != s.end());
            REQUIRE(s.cbegin() != s.cend());

            REQUIRE(s.end() - s.begin() == 1 * sizeof(int));
            REQUIRE(s.cend() - s.cbegin() == 1 * sizeof(int));

            REQUIRE(std::equal(std::begin(s),
                               std::end(s),
                               reinterpret_cast<cmm::byte*>(source.data())));

            REQUIRE(std::equal(std::cbegin(s),
                               std::cend(s),
                               reinterpret_cast<const cmm::byte*>(source.data())));

            for (auto i = 0; i < static_cast<int>(sizeof(int) * source.size()); i++)
                REQUIRE(s[i] == reinterpret_cast<cmm::byte*>(source.data())[i]);
        }

        SECTION("from (ptr, size) pair")
        {
            float source[] = {3.4f};
            cmm::cspan s{source, sizeof(float)};

            REQUIRE((void*) s.data() == (void*) source);
            REQUIRE(s.size() == 1 * sizeof(float));
            REQUIRE(s.size_bytes() == 1 * sizeof(float));

            REQUIRE(s.begin() != s.end());
            REQUIRE(s.cbegin() != s.cend());

            REQUIRE(s.end() - s.begin() == 1 * sizeof(float));
            REQUIRE(s.cend() - s.cbegin() == 1 * sizeof(float));

            REQUIRE(std::equal(std::begin(s),
                               std::end(s),
                               reinterpret_cast<cmm::byte*>(&source)));

            REQUIRE(std::equal(std::cbegin(s),
                               std::cend(s),
                               reinterpret_cast<const cmm::byte*>(&source)));

            for (auto i = 0; i < static_cast<int>(sizeof(float)); i++)
                REQUIRE(s[i] == reinterpret_cast<cmm::byte*>(&source)[i]);
        }
    }
}
