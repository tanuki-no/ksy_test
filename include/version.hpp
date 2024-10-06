/*!
 *	\file		version.hpp
 *	\brief		Declares ksy test version and defaults
 *	\author		Vladislav "Tanuki" Mikhailikov \<vmikhailikov\@gmail.com\>
 *	\copyright	GNU GPL v3
 *	\date		05.10.2024
 *	\version	1.0
 */

#ifndef KSY_TEST_VERSION
#define KSY_TEST_VERSION

#include <string>


namespace mts
{
namespace test
{

/// Library version
struct version
{
  /// Library release
  static const int          major;

  /// Library branch
  static const int          minor;

  /// Library patch information
  static const int          patch;

  /// Library tweak information
  static const int          tweak;

  /// Library combined information
  static const std::string  full;
};

std::string& name(void);

} // End of mts::test namespace
} // End of mts namespace

#endif  // KSY_TEST_VERSION

/* End of file */