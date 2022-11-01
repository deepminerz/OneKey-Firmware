/*
 * This file is part of the Trezor project, https://trezor.io/
 *
 * Copyright (C) 2018 Pavol Rusnak <stick@satoshilabs.com>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <string.h>

#include "br_check.h"
#include "image.h"
#include "sha2.h"

static char boardloader_version[32] = {0};

static int onekey_known_boardloader(const uint8_t *hash) {
  if (0 ==
      memcmp(hash,
             "\x5b\xd1\xcd\x80\xa3\xbd\xa4\xa2\xf0\x84\x89\xec\x09\x9a\xad\xbb"
             "\xa6\x52\xd9\xb3\x1c\x1c\xfc\x90\xb1\x93\x43\x66\x1e\x8b\x8d\x6c",
             32)) {
    memcpy(boardloader_version, "1.0.0", strlen("1.0.0"));
    return 1;
  }
  if (0 ==
      memcmp(hash,
             "\x01\x0f\x28\xc2\x08\x2d\x90\xce\x18\xc0\x35\x2d\x0d\xb9\x0d\xa7"
             "\x6c\x61\x00\xf9\xfb\x05\x5b\xad\xef\x37\x53\x8a\xea\x44\x50\x78",
             32)) {
    memcpy(boardloader_version, "1.1.0", strlen("1.1.0"));
    return 1;  // 1.9.0
  }
  memcpy(boardloader_version, "unkonw boardloader",
         strlen("unkonw boardloader"));
  return 1;
}

char *get_boardloader_version(void) {
  uint8_t hash[32] = {0};

  if (strlen(boardloader_version) == 0) {
    sha256_Raw((uint8_t *)BOARDLOADER_START,
               BOOTLOADER_START - BOARDLOADER_START, hash);
    sha256_Raw(hash, 32, hash);

    onekey_known_boardloader(hash);
  }

  return boardloader_version;
}