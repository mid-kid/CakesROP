/*
  types.h _ Various system types.
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define U64_MAX	UINT64_MAX

typedef enum
{
	mediatype_NAND,
	mediatype_SDMC,
	mediatype_GAMECARD,
} mediatypes_enum;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;

typedef volatile s8 vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

typedef u32 Handle;
typedef s32 Result;
typedef void (*ThreadFunc)(void *);

#define BIT(n) (1U<<(n))

//! aligns a struct (and other types?) to m, making sure that the size of the struct is a multiple of m.
#define ALIGN(m)	__attribute__((aligned (m)))

//! packs a struct (and other types?) so it won't include padding bytes.
#define PACKED __attribute__ ((packed))

struct PACKED KCodeSet {
	/* 00 */ u8 padding1[0x5c - 0x00];
	/* 5c */ u64 titleid;
};

struct KProcess4 {
	/* 00 */ void *vtable;
	/* 04 */ u8 padding1[0xA0 - 0x04];
	/* a0 */ u32 exheader_flags;
	/* a4 */ u8 padding2[0xA8 - 0xA4];
	/* a8 */ struct KCodeSet *code_set;
	/* ac */ u32 pid;
};

struct KProcess8 {
	/* 00 */ void *vtable;
	/* 04 */ u8 padding1[0xA8 - 0x04];
	/* a8 */ u32 exheader_flags;
	/* ac */ u8 padding2[0xB0 - 0xAC];
	/* b0 */ struct KCodeSet *code_set;
	/* b4 */ u32 pid;
};

struct PACKED SVCRegisterState {
	u32 m_r4;
	u32 m_r5;
	u32 m_r6;
	u32 m_r7;
	u32 m_r8;
	u32 m_r9;
	u32 m_sl;
	u32 m_fp;
	u32 m_sp;
	u32 m_lr;
};

struct PACKED KThread {
	/* 00 */ u8 padding1[0x88 - 0x00];
	/* 88 */ struct SVCRegisterState *svc_register_state;
};

struct PACKED SVCThreadArea {
	/* 00 */ u8 svc_acl[0x10];
	/* 10 */ u8 padding[0x18 - 0x10];
	/* 18 */ struct SVCRegisterState svc_register_state;
};

