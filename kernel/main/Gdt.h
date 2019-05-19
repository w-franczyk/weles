#pragma once

// just segment definitions initialized by the bootloader
// until the kernel wouldn't reinitialize it
namespace Gdt
{

constexpr std::uint8_t codeSegment = 0x8;
constexpr std::uint8_t dataSegment = 0x10;

} // namespace Gdt
