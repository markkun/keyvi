/* * keyvi - A key value store.
 *
 * Copyright 2015 Hendrik Muhs<hendrik.muhs@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * constants.h
 *
 *  Created on: May 5, 2014
 *      Author: hendrik
 */

#ifndef KEYVI_DICTIONARY_FSA_INTERNAL_CONSTANTS_H_
#define KEYVI_DICTIONARY_FSA_INTERNAL_CONSTANTS_H_

#include <cstddef>
#include <cstdint>

// file format definitions

// file magic
static const char KEYVI_FILE_MAGIC[] = "KEYVIFSA";
static const size_t KEYVI_FILE_MAGIC_LEN = 8;

// min version of the file
static const int KEYVI_FILE_VERSION_MIN = 2;

// min version of the persistence part
static const int KEYVI_FILE_PERSISTENCE_VERSION_MIN = 2;
static const size_t NUMBER_OF_STATE_CODINGS = 255;
static const uint16_t FINAL_OFFSET_TRANSITION = 256;
static const size_t FINAL_OFFSET_CODE = 1;
static const size_t INNER_WEIGHT_TRANSITION_COMPACT = 260;
static const size_t MAX_TRANSITIONS_OF_A_STATE = 261;

// Compact mode definitions
static const size_t COMPACT_SIZE_RELATIVE_MAX_VALUE = 32768;
static const size_t COMPACT_SIZE_ABSOLUTE_MAX_VALUE = 16384;
static const size_t COMPACT_SIZE_WINDOW = 512;
static const size_t COMPACT_SIZE_INNER_WEIGHT_MAX_VALUE = 0xffff;

// how many buckets to go left doing (brute force) search for free buckets in
// the sparse array where the new state fits in
static const size_t SPARSE_ARRAY_SEARCH_OFFSET = 151;

// 1 GB default memory limit for the sorter (tpie)
static const size_t DEFAULT_MEMORY_LIMIT_TPIE_SORT = 1 * 1024 * 1024 * 1024;

// 1 GB default memory limit for the generator
static const size_t DEFAULT_MEMORY_LIMIT_GENERATOR = 1 * 1024 * 1024 * 1024;

// 500MB default memory limit for value stores
static const size_t DEFAULT_MEMORY_LIMIT_VALUE_STORE = 500 * 1024 * 1024;

// option key names
static const char MEMORY_LIMIT_KEY[] = "memory_limit";
static const char TEMPORARY_PATH_KEY[] = "temporary_path";
static const char COMPRESSION_KEY[] = "compression";
static const char COMPRESSION_THRESHOLD_KEY[] = "compression_threshold";
static const char MINIMIZATION_KEY[] = "minimization";
static const char SINGLE_PRECISION_FLOAT_KEY[] = "floating_point_precision";
static const char STABLE_INSERTS[] = "stable_insert";
static const char MERGE_MODE[] = "merge_mode";
static const char MERGE_APPEND[] = "append";

/**
 * Lookup table to find outgoing transitions quickly(in parallel) by xor'ing the
 * real buffer with this table.
 * (also used for the intrinsic(SSE 4.2) based implementation)
 */
static unsigned char OUTGOING_TRANSITIONS_MASK[256] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12,
    0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
    0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
    0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b,
    0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e,
    0x5f, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71,
    0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x82, 0x83, 0x84,
    0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
    0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa,
    0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd,
    0xbe, 0xbf, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0,
    0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf, 0xe0, 0xe1, 0xe2, 0xe3,
    0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6,
    0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff};

#endif  // KEYVI_DICTIONARY_FSA_INTERNAL_CONSTANTS_H_