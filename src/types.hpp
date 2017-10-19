#pragma once

#include <cstdint>

#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <functional>

#include <gsl/span>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using BufferSpan = gsl::span<const u8>;
using BufferIndexType = BufferSpan::index_type;
using WriterCallback = std::function<void(const BufferSpan& buffer)>;
using ReaderCallback = std::function<void(const BufferSpan& buffer, const WriterCallback& writer)>;
