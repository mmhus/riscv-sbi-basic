#include "sbi_common.h"

#define EID_10 0x10ul

struct sbiret sbi_get_spec_version(void) {
  return sbi_inner_wrapper(EID_10, FID_0);
}

struct sbiret sbi_get_impl_id(void) {

}

struct sbiret sbi_get_impl_version(void) {

}

struct sbiret sbi_probe_extension(long extension_id) {

}

struct sbiret sbi_get_mvendorid(void) {

}

struct sbiret sbi_get_marchid(void) {

}

struct sbiret sbi_get_mimpid(void) {

}