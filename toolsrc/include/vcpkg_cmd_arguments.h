#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include "opt_bool.h"
#include "package_spec.h"
#include "vcpkg_paths.h"
#include "StatusParagraphs.h"

namespace vcpkg
{
    struct vcpkg_cmd_arguments
    {
        static vcpkg_cmd_arguments create_from_command_line(const int argc, const wchar_t* const* const argv);
        static vcpkg_cmd_arguments create_from_arg_sequence(const std::string* arg_begin, const std::string* arg_end);

        static package_spec check_and_get_package_spec(const std::string& package_spec_as_string, const triplet& default_target_triplet, const char* example_text);
        static std::vector<package_spec> check_and_get_package_specs(const std::vector<std::string>& package_specs_as_strings, const triplet& default_target_triplet, const char* example_text);

        std::unique_ptr<std::string> vcpkg_root_dir;
        std::unique_ptr<std::string> target_triplet;
        opt_bool debug = opt_bool::unspecified;
        opt_bool sendmetrics = opt_bool::unspecified;
        opt_bool printmetrics = opt_bool::unspecified;

        std::string command;
        std::vector<std::string> command_arguments;
        std::unordered_set<std::string> check_and_get_optional_command_arguments(const std::vector<std::string>& valid_options) const;

        void check_max_arg_count(const size_t expected_arg_count) const;
        void check_max_arg_count(const size_t expected_arg_count, const char* example_text) const;
        void check_min_arg_count(const size_t expected_arg_count) const;
        void check_min_arg_count(const size_t expected_arg_count, const char* example_text) const;
        void check_exact_arg_count(const size_t expected_arg_count) const;
        void check_exact_arg_count(const size_t expected_arg_count, const char* example_text) const;

        std::vector<package_spec> parse_all_arguments_as_package_specs(const triplet& default_target_triplet, const char* example_text = nullptr) const;

    private:
        std::unordered_set<std::string> optional_command_arguments;
    };
}
