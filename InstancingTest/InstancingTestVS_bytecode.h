#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 6.3.9600.16384
//
//
// Buffer Definitions: 
//
// cbuffer cbVSPerObject
// {
//
//   float4x4 View;                     // Offset:    0 Size:    64
//   float4x4 Proj;                     // Offset:   64 Size:    64
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// cbVSPerObject                     cbuffer      NA          NA    0        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// POSITION                 0   xyz         0     NONE   float   xyz 
// NORMAL                   0   xyz         1     NONE   float   xyz 
// BLENDINDICES             0   xyzw        2     NONE    uint   xyzw
// BLENDWEIGHT              0   xyzw        3     NONE   float   xyzw
// INSTANCE_WORLD           0   xyzw        4     NONE   float   xyzw
// INSTANCE_WORLD           1   xyzw        5     NONE   float   xyzw
// INSTANCE_WORLD           2   xyzw        6     NONE   float   xyzw
// INSTANCE_WORLD           3   xyzw        7     NONE   float   xyzw
// INSTANCE_BONE            0   xyzw        8     NONE   float   xyzw
// INSTANCE_BONE            1   xyzw        9     NONE   float   xyzw
// INSTANCE_BONE            2   xyzw       10     NONE   float   xyzw
// INSTANCE_BONE            3   xyzw       11     NONE   float   xyzw
// INSTANCE_BONE            4   xyzw       12     NONE   float   xyzw
// INSTANCE_BONE            5   xyzw       13     NONE   float   xyzw
// INSTANCE_BONE            6   xyzw       14     NONE   float   xyzw
// INSTANCE_BONE            7   xyzw       15     NONE   float   xyzw
// INSTANCE_BONE            8   xyzw       16     NONE   float   xyzw
// INSTANCE_BONE            9   xyzw       17     NONE   float   xyzw
// INSTANCE_BONE           10   xyzw       18     NONE   float   xyzw
// INSTANCE_BONE           11   xyzw       19     NONE   float   xyzw
// INSTANCE_BONE           12   xyzw       20     NONE   float   xyzw
// INSTANCE_BONE           13   xyzw       21     NONE   float   xyzw
// INSTANCE_BONE           14   xyzw       22     NONE   float   xyzw
// INSTANCE_BONE           15   xyzw       23     NONE   float   xyzw
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Position              0   xyzw        0      POS   float   xyzw
// NORMAL                   0   xyz         1     NONE   float   xyz 
//
vs_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer cb0[8], immediateIndexed
dcl_input v0.xyz
dcl_input v1.xyz
dcl_input v2.xyzw
dcl_input v3.xyzw
dcl_input v4.xyzw
dcl_input v5.xyzw
dcl_input v6.xyzw
dcl_input v7.xyzw
dcl_input v8.xyzw
dcl_input v9.xyzw
dcl_input v10.xyzw
dcl_input v11.xyzw
dcl_input v12.xyzw
dcl_input v13.xyzw
dcl_input v14.xyzw
dcl_input v15.xyzw
dcl_input v16.xyzw
dcl_input v17.xyzw
dcl_input v18.xyzw
dcl_input v19.xyzw
dcl_input v20.xyzw
dcl_input v21.xyzw
dcl_input v22.xyzw
dcl_input v23.xyzw
dcl_output_siv o0.xyzw, position
dcl_output o1.xyz
dcl_temps 20
dcl_indexrange v8.xyzw 16
ishl r0.xyzw, v2.xyzw, l(2, 2, 2, 2)
mov r1.x, v[r0.y + 8].w
mov r1.y, v[r0.y + 9].w
mov r1.z, v[r0.y + 10].w
mov r1.w, v[r0.y + 11].w
mul r1.xyzw, r1.xyzw, v3.yyyy
mov r2.x, v[r0.x + 8].w
mov r2.y, v[r0.x + 9].w
mov r2.z, v[r0.x + 10].w
mov r2.w, v[r0.x + 11].w
mad r1.xyzw, r2.xyzw, v3.xxxx, r1.xyzw
mov r2.x, v[r0.z + 8].w
mov r2.y, v[r0.z + 9].w
mov r2.z, v[r0.z + 10].w
mov r2.w, v[r0.z + 11].w
mad r1.xyzw, r2.xyzw, v3.zzzz, r1.xyzw
mov r2.x, v[r0.w + 8].w
mov r2.y, v[r0.w + 9].w
mov r2.z, v[r0.w + 10].w
mov r2.w, v[r0.w + 11].w
mad r1.xyzw, r2.xyzw, v3.wwww, r1.xyzw
dp4 r2.x, r1.xyzw, v4.xyzw
dp4 r2.y, r1.xyzw, v5.xyzw
dp4 r2.z, r1.xyzw, v6.xyzw
dp4 r2.w, r1.xyzw, v7.xyzw
dp4 r1.w, r2.xyzw, cb0[3].xyzw
mul r3.xyz, v3.xxxx, v[r0.x + 8].yxzy
mov r4.x, r3.y
mul r5.xyz, v3.xxxx, v[r0.x + 9].xzyx
mov r4.y, r5.x
mul r6.xyz, v3.xxxx, v[r0.x + 10].xyzx
mov r4.z, r6.x
mul r7.xyz, v3.xxxx, v[r0.x + 11].xyzx
mov r4.w, r7.x
mul r8.xyz, v3.yyyy, v[r0.y + 8].yxzy
mov r9.x, r8.y
mul r10.xyz, v3.yyyy, v[r0.y + 9].xzyx
mov r9.y, r10.x
mul r11.xyz, v3.yyyy, v[r0.y + 10].xyzx
mov r9.z, r11.x
mul r12.xyz, v3.yyyy, v[r0.y + 11].xyzx
mov r9.w, r12.x
add r4.xyzw, r4.xyzw, r9.xyzw
mul r9.xyz, v3.zzzz, v[r0.z + 8].yxzy
mov r13.x, r9.y
mul r14.xyz, v3.zzzz, v[r0.z + 9].xzyx
mov r13.y, r14.x
mul r15.xyz, v3.zzzz, v[r0.z + 10].xyzx
mov r13.z, r15.x
mul r0.xyz, v3.zzzz, v[r0.z + 11].xyzx
mov r13.w, r0.x
add r4.xyzw, r4.xyzw, r13.xyzw
mul r13.xyz, v3.wwww, v[r0.w + 8].yxzy
mov r16.x, r13.y
mul r17.xyz, v3.wwww, v[r0.w + 9].xzyx
mov r16.y, r17.x
mul r18.xyz, v3.wwww, v[r0.w + 10].xyzx
mul r19.xyz, v3.wwww, v[r0.w + 11].xyzx
mov r16.z, r18.x
mov r16.w, r19.x
add r4.xyzw, r4.xyzw, r16.xyzw
dp4 r16.x, r4.xyzw, v4.xyzw
dp4 r16.y, r4.xyzw, v5.xyzw
dp4 r16.z, r4.xyzw, v6.xyzw
dp4 r16.w, r4.xyzw, v7.xyzw
dp4 r1.x, r16.xyzw, cb0[3].xyzw
mov r5.x, r3.z
mov r3.y, r5.z
mov r3.z, r6.y
mov r5.z, r6.z
mov r3.w, r7.y
mov r5.w, r7.z
mov r10.x, r8.z
mov r8.y, r10.z
mov r8.z, r11.y
mov r10.z, r11.z
mov r8.w, r12.y
mov r10.w, r12.z
add r4.xyzw, r5.xyzw, r10.xyzw
add r3.xyzw, r3.xyzw, r8.xyzw
mov r14.x, r9.z
mov r9.y, r14.z
mov r9.z, r15.y
mov r14.z, r15.z
mov r9.w, r0.y
mov r14.w, r0.z
add r0.xyzw, r4.xyzw, r14.xyzw
add r3.xyzw, r3.xyzw, r9.xyzw
mov r17.x, r13.z
mov r13.y, r17.z
mov r13.z, r18.y
mov r17.z, r18.z
mov r13.w, r19.y
mov r17.w, r19.z
add r0.xyzw, r0.xyzw, r17.xyzw
add r3.xyzw, r3.xyzw, r13.xyzw
dp4 r4.x, r3.xyzw, v4.xyzw
dp4 r4.y, r3.xyzw, v5.xyzw
dp4 r4.z, r3.xyzw, v6.xyzw
dp4 r4.w, r3.xyzw, v7.xyzw
dp4 r1.y, r4.xyzw, cb0[3].xyzw
dp4 r3.x, r0.xyzw, v4.xyzw
dp4 r3.y, r0.xyzw, v5.xyzw
dp4 r3.z, r0.xyzw, v6.xyzw
dp4 r3.w, r0.xyzw, v7.xyzw
dp4 r1.z, r3.xyzw, cb0[3].xyzw
mov r0.xyz, v0.xyzx
mov r0.w, l(1.000000)
dp4 r1.w, r0.xyzw, r1.xyzw
dp4 r5.x, r16.xyzw, cb0[0].xyzw
dp4 r5.y, r4.xyzw, cb0[0].xyzw
dp4 r5.z, r3.xyzw, cb0[0].xyzw
dp4 r5.w, r2.xyzw, cb0[0].xyzw
dp4 r1.x, r0.xyzw, r5.xyzw
dp3 o1.x, v1.xyzx, r5.xyzx
dp4 r5.w, r2.xyzw, cb0[1].xyzw
dp4 r2.w, r2.xyzw, cb0[2].xyzw
dp4 r5.x, r16.xyzw, cb0[1].xyzw
dp4 r2.x, r16.xyzw, cb0[2].xyzw
dp4 r5.y, r4.xyzw, cb0[1].xyzw
dp4 r2.y, r4.xyzw, cb0[2].xyzw
dp4 r5.z, r3.xyzw, cb0[1].xyzw
dp4 r2.z, r3.xyzw, cb0[2].xyzw
dp4 r1.y, r0.xyzw, r5.xyzw
dp3 o1.y, v1.xyzx, r5.xyzx
dp4 r1.z, r0.xyzw, r2.xyzw
dp3 o1.z, v1.xyzx, r2.xyzx
dp4 o0.x, r1.xyzw, cb0[4].xyzw
dp4 o0.y, r1.xyzw, cb0[5].xyzw
dp4 o0.z, r1.xyzw, cb0[6].xyzw
dp4 o0.w, r1.xyzw, cb0[7].xyzw
ret 
// Approximately 132 instruction slots used
#endif

const BYTE g_InstancingTestVS_bytecode[] =
{
     68,  88,  66,  67, 207, 161, 
    116,  54,  73, 249, 115,  43, 
    169, 180,  60, 127, 166,  84, 
    214, 133,   1,   0,   0,   0, 
    120,  20,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
    124,   1,   0,   0,  20,   4, 
      0,   0, 104,   4,   0,   0, 
    220,  19,   0,   0,  82,  68, 
     69,  70,  64,   1,   0,   0, 
      1,   0,   0,   0, 108,   0, 
      0,   0,   1,   0,   0,   0, 
     60,   0,   0,   0,   0,   5, 
    254, 255,   0,   1,   0,   0, 
     13,   1,   0,   0,  82,  68, 
     49,  49,  60,   0,   0,   0, 
     24,   0,   0,   0,  32,   0, 
      0,   0,  40,   0,   0,   0, 
     36,   0,   0,   0,  12,   0, 
      0,   0,   0,   0,   0,   0, 
     92,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  99,  98,  86,  83, 
     80, 101, 114,  79,  98, 106, 
    101,  99, 116,   0, 171, 171, 
     92,   0,   0,   0,   2,   0, 
      0,   0, 132,   0,   0,   0, 
    128,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    212,   0,   0,   0,   0,   0, 
      0,   0,  64,   0,   0,   0, 
      2,   0,   0,   0, 228,   0, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,   8,   1, 
      0,   0,  64,   0,   0,   0, 
     64,   0,   0,   0,   2,   0, 
      0,   0, 228,   0,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,  86, 105, 101, 119, 
      0, 102, 108, 111,  97, 116, 
     52, 120,  52,   0, 171, 171, 
      3,   0,   3,   0,   4,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 217,   0,   0,   0, 
     80, 114, 111, 106,   0,  77, 
    105,  99, 114, 111, 115, 111, 
    102, 116,  32,  40,  82,  41, 
     32,  72,  76,  83,  76,  32, 
     83, 104,  97, 100, 101, 114, 
     32,  67, 111, 109, 112, 105, 
    108, 101, 114,  32,  54,  46, 
     51,  46,  57,  54,  48,  48, 
     46,  49,  54,  51,  56,  52, 
      0, 171,  73,  83,  71,  78, 
    144,   2,   0,   0,  24,   0, 
      0,   0,   8,   0,   0,   0, 
     72,   2,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   7,   7,   0,   0, 
     81,   2,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,   7,   7,   0,   0, 
     88,   2,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   2,   0, 
      0,   0,  15,  15,   0,   0, 
    101,   2,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   3,   0, 
      0,   0,  15,  15,   0,   0, 
    113,   2,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   4,   0, 
      0,   0,  15,  15,   0,   0, 
    113,   2,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   5,   0, 
      0,   0,  15,  15,   0,   0, 
    113,   2,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   6,   0, 
      0,   0,  15,  15,   0,   0, 
    113,   2,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   7,   0, 
      0,   0,  15,  15,   0,   0, 
    128,   2,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   8,   0, 
      0,   0,  15,  15,   0,   0, 
    128,   2,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   9,   0, 
      0,   0,  15,  15,   0,   0, 
    128,   2,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  10,   0, 
      0,   0,  15,  15,   0,   0, 
    128,   2,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  11,   0, 
      0,   0,  15,  15,   0,   0, 
    128,   2,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  12,   0, 
      0,   0,  15,  15,   0,   0, 
    128,   2,   0,   0,   5,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  13,   0, 
      0,   0,  15,  15,   0,   0, 
    128,   2,   0,   0,   6,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  14,   0, 
      0,   0,  15,  15,   0,   0, 
    128,   2,   0,   0,   7,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  15,   0, 
      0,   0,  15,  15,   0,   0, 
    128,   2,   0,   0,   8,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  16,   0, 
      0,   0,  15,  15,   0,   0, 
    128,   2,   0,   0,   9,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  17,   0, 
      0,   0,  15,  15,   0,   0, 
    128,   2,   0,   0,  10,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  18,   0, 
      0,   0,  15,  15,   0,   0, 
    128,   2,   0,   0,  11,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  19,   0, 
      0,   0,  15,  15,   0,   0, 
    128,   2,   0,   0,  12,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  20,   0, 
      0,   0,  15,  15,   0,   0, 
    128,   2,   0,   0,  13,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  21,   0, 
      0,   0,  15,  15,   0,   0, 
    128,   2,   0,   0,  14,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  22,   0, 
      0,   0,  15,  15,   0,   0, 
    128,   2,   0,   0,  15,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  23,   0, 
      0,   0,  15,  15,   0,   0, 
     80,  79,  83,  73,  84,  73, 
     79,  78,   0,  78,  79,  82, 
     77,  65,  76,   0,  66,  76, 
     69,  78,  68,  73,  78,  68, 
     73,  67,  69,  83,   0,  66, 
     76,  69,  78,  68,  87,  69, 
     73,  71,  72,  84,   0,  73, 
     78,  83,  84,  65,  78,  67, 
     69,  95,  87,  79,  82,  76, 
     68,   0,  73,  78,  83,  84, 
     65,  78,  67,  69,  95,  66, 
     79,  78,  69,   0, 171, 171, 
     79,  83,  71,  78,  76,   0, 
      0,   0,   2,   0,   0,   0, 
      8,   0,   0,   0,  56,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  68,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
      7,   8,   0,   0,  83,  86, 
     95,  80, 111, 115, 105, 116, 
    105, 111, 110,   0,  78,  79, 
     82,  77,  65,  76,   0, 171, 
     83,  72,  69,  88, 108,  15, 
      0,   0,  80,   0,   1,   0, 
    219,   3,   0,   0, 106,   8, 
      0,   1,  89,   0,   0,   4, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   8,   0,   0,   0, 
     95,   0,   0,   3, 114,  16, 
     16,   0,   0,   0,   0,   0, 
     95,   0,   0,   3, 114,  16, 
     16,   0,   1,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   2,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   3,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   4,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   5,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   6,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   7,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   8,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   9,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,  10,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,  11,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,  12,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,  13,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,  14,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,  15,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,  16,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,  17,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,  18,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,  19,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,  20,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,  21,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,  22,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,  23,   0,   0,   0, 
    103,   0,   0,   4, 242,  32, 
     16,   0,   0,   0,   0,   0, 
      1,   0,   0,   0, 101,   0, 
      0,   3, 114,  32,  16,   0, 
      1,   0,   0,   0, 104,   0, 
      0,   2,  20,   0,   0,   0, 
     91,   0,   0,   4, 242,  16, 
     16,   0,   8,   0,   0,   0, 
     16,   0,   0,   0,  41,   0, 
      0,  10, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,  30, 
     16,   0,   2,   0,   0,   0, 
      2,  64,   0,   0,   2,   0, 
      0,   0,   2,   0,   0,   0, 
      2,   0,   0,   0,   2,   0, 
      0,   0,  54,   0,   0,   7, 
     18,   0,  16,   0,   1,   0, 
      0,   0,  58,  16, 208,   0, 
      8,   0,   0,   0,  26,   0, 
     16,   0,   0,   0,   0,   0, 
     54,   0,   0,   7,  34,   0, 
     16,   0,   1,   0,   0,   0, 
     58,  16, 208,   0,   9,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   7,  66,   0,  16,   0, 
      1,   0,   0,   0,  58,  16, 
    208,   0,  10,   0,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  54,   0,   0,   7, 
    130,   0,  16,   0,   1,   0, 
      0,   0,  58,  16, 208,   0, 
     11,   0,   0,   0,  26,   0, 
     16,   0,   0,   0,   0,   0, 
     56,   0,   0,   7, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  86,  21,  16,   0, 
      3,   0,   0,   0,  54,   0, 
      0,   7,  18,   0,  16,   0, 
      2,   0,   0,   0,  58,  16, 
    208,   0,   8,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,  54,   0,   0,   7, 
     34,   0,  16,   0,   2,   0, 
      0,   0,  58,  16, 208,   0, 
      9,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     54,   0,   0,   7,  66,   0, 
     16,   0,   2,   0,   0,   0, 
     58,  16, 208,   0,  10,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   7, 130,   0,  16,   0, 
      2,   0,   0,   0,  58,  16, 
    208,   0,  11,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,  50,   0,   0,   9, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,   6,  16, 
     16,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  54,   0,   0,   7, 
     18,   0,  16,   0,   2,   0, 
      0,   0,  58,  16, 208,   0, 
      8,   0,   0,   0,  42,   0, 
     16,   0,   0,   0,   0,   0, 
     54,   0,   0,   7,  34,   0, 
     16,   0,   2,   0,   0,   0, 
     58,  16, 208,   0,   9,   0, 
      0,   0,  42,   0,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   7,  66,   0,  16,   0, 
      2,   0,   0,   0,  58,  16, 
    208,   0,  10,   0,   0,   0, 
     42,   0,  16,   0,   0,   0, 
      0,   0,  54,   0,   0,   7, 
    130,   0,  16,   0,   2,   0, 
      0,   0,  58,  16, 208,   0, 
     11,   0,   0,   0,  42,   0, 
     16,   0,   0,   0,   0,   0, 
     50,   0,   0,   9, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0, 166,  26,  16,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     54,   0,   0,   7,  18,   0, 
     16,   0,   2,   0,   0,   0, 
     58,  16, 208,   0,   8,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   7,  34,   0,  16,   0, 
      2,   0,   0,   0,  58,  16, 
    208,   0,   9,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  54,   0,   0,   7, 
     66,   0,  16,   0,   2,   0, 
      0,   0,  58,  16, 208,   0, 
     10,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     54,   0,   0,   7, 130,   0, 
     16,   0,   2,   0,   0,   0, 
     58,  16, 208,   0,  11,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,   9, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
    246,  31,  16,   0,   3,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  17,   0, 
      0,   7,  18,   0,  16,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70,  30,  16,   0,   4,   0, 
      0,   0,  17,   0,   0,   7, 
     34,   0,  16,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  70,  30, 
     16,   0,   5,   0,   0,   0, 
     17,   0,   0,   7,  66,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  70,  30,  16,   0, 
      6,   0,   0,   0,  17,   0, 
      0,   7, 130,   0,  16,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70,  30,  16,   0,   7,   0, 
      0,   0,  17,   0,   0,   8, 
    130,   0,  16,   0,   1,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  56,   0, 
      0,   9, 114,   0,  16,   0, 
      3,   0,   0,   0,   6,  16, 
     16,   0,   3,   0,   0,   0, 
     22,  22, 208,   0,   8,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   5,  18,   0,  16,   0, 
      4,   0,   0,   0,  26,   0, 
     16,   0,   3,   0,   0,   0, 
     56,   0,   0,   9, 114,   0, 
     16,   0,   5,   0,   0,   0, 
      6,  16,  16,   0,   3,   0, 
      0,   0, 134,  17, 208,   0, 
      9,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     54,   0,   0,   5,  34,   0, 
     16,   0,   4,   0,   0,   0, 
     10,   0,  16,   0,   5,   0, 
      0,   0,  56,   0,   0,   9, 
    114,   0,  16,   0,   6,   0, 
      0,   0,   6,  16,  16,   0, 
      3,   0,   0,   0,  70,  18, 
    208,   0,  10,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,  54,   0,   0,   5, 
     66,   0,  16,   0,   4,   0, 
      0,   0,  10,   0,  16,   0, 
      6,   0,   0,   0,  56,   0, 
      0,   9, 114,   0,  16,   0, 
      7,   0,   0,   0,   6,  16, 
     16,   0,   3,   0,   0,   0, 
     70,  18, 208,   0,  11,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   5, 130,   0,  16,   0, 
      4,   0,   0,   0,  10,   0, 
     16,   0,   7,   0,   0,   0, 
     56,   0,   0,   9, 114,   0, 
     16,   0,   8,   0,   0,   0, 
     86,  21,  16,   0,   3,   0, 
      0,   0,  22,  22, 208,   0, 
      8,   0,   0,   0,  26,   0, 
     16,   0,   0,   0,   0,   0, 
     54,   0,   0,   5,  18,   0, 
     16,   0,   9,   0,   0,   0, 
     26,   0,  16,   0,   8,   0, 
      0,   0,  56,   0,   0,   9, 
    114,   0,  16,   0,  10,   0, 
      0,   0,  86,  21,  16,   0, 
      3,   0,   0,   0, 134,  17, 
    208,   0,   9,   0,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  54,   0,   0,   5, 
     34,   0,  16,   0,   9,   0, 
      0,   0,  10,   0,  16,   0, 
     10,   0,   0,   0,  56,   0, 
      0,   9, 114,   0,  16,   0, 
     11,   0,   0,   0,  86,  21, 
     16,   0,   3,   0,   0,   0, 
     70,  18, 208,   0,  10,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   5,  66,   0,  16,   0, 
      9,   0,   0,   0,  10,   0, 
     16,   0,  11,   0,   0,   0, 
     56,   0,   0,   9, 114,   0, 
     16,   0,  12,   0,   0,   0, 
     86,  21,  16,   0,   3,   0, 
      0,   0,  70,  18, 208,   0, 
     11,   0,   0,   0,  26,   0, 
     16,   0,   0,   0,   0,   0, 
     54,   0,   0,   5, 130,   0, 
     16,   0,   9,   0,   0,   0, 
     10,   0,  16,   0,  12,   0, 
      0,   0,   0,   0,   0,   7, 
    242,   0,  16,   0,   4,   0, 
      0,   0,  70,  14,  16,   0, 
      4,   0,   0,   0,  70,  14, 
     16,   0,   9,   0,   0,   0, 
     56,   0,   0,   9, 114,   0, 
     16,   0,   9,   0,   0,   0, 
    166,  26,  16,   0,   3,   0, 
      0,   0,  22,  22, 208,   0, 
      8,   0,   0,   0,  42,   0, 
     16,   0,   0,   0,   0,   0, 
     54,   0,   0,   5,  18,   0, 
     16,   0,  13,   0,   0,   0, 
     26,   0,  16,   0,   9,   0, 
      0,   0,  56,   0,   0,   9, 
    114,   0,  16,   0,  14,   0, 
      0,   0, 166,  26,  16,   0, 
      3,   0,   0,   0, 134,  17, 
    208,   0,   9,   0,   0,   0, 
     42,   0,  16,   0,   0,   0, 
      0,   0,  54,   0,   0,   5, 
     34,   0,  16,   0,  13,   0, 
      0,   0,  10,   0,  16,   0, 
     14,   0,   0,   0,  56,   0, 
      0,   9, 114,   0,  16,   0, 
     15,   0,   0,   0, 166,  26, 
     16,   0,   3,   0,   0,   0, 
     70,  18, 208,   0,  10,   0, 
      0,   0,  42,   0,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   5,  66,   0,  16,   0, 
     13,   0,   0,   0,  10,   0, 
     16,   0,  15,   0,   0,   0, 
     56,   0,   0,   9, 114,   0, 
     16,   0,   0,   0,   0,   0, 
    166,  26,  16,   0,   3,   0, 
      0,   0,  70,  18, 208,   0, 
     11,   0,   0,   0,  42,   0, 
     16,   0,   0,   0,   0,   0, 
     54,   0,   0,   5, 130,   0, 
     16,   0,  13,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,   0,   0,   0,   7, 
    242,   0,  16,   0,   4,   0, 
      0,   0,  70,  14,  16,   0, 
      4,   0,   0,   0,  70,  14, 
     16,   0,  13,   0,   0,   0, 
     56,   0,   0,   9, 114,   0, 
     16,   0,  13,   0,   0,   0, 
    246,  31,  16,   0,   3,   0, 
      0,   0,  22,  22, 208,   0, 
      8,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     54,   0,   0,   5,  18,   0, 
     16,   0,  16,   0,   0,   0, 
     26,   0,  16,   0,  13,   0, 
      0,   0,  56,   0,   0,   9, 
    114,   0,  16,   0,  17,   0, 
      0,   0, 246,  31,  16,   0, 
      3,   0,   0,   0, 134,  17, 
    208,   0,   9,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  54,   0,   0,   5, 
     34,   0,  16,   0,  16,   0, 
      0,   0,  10,   0,  16,   0, 
     17,   0,   0,   0,  56,   0, 
      0,   9, 114,   0,  16,   0, 
     18,   0,   0,   0, 246,  31, 
     16,   0,   3,   0,   0,   0, 
     70,  18, 208,   0,  10,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   9, 114,   0,  16,   0, 
     19,   0,   0,   0, 246,  31, 
     16,   0,   3,   0,   0,   0, 
     70,  18, 208,   0,  11,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   5,  66,   0,  16,   0, 
     16,   0,   0,   0,  10,   0, 
     16,   0,  18,   0,   0,   0, 
     54,   0,   0,   5, 130,   0, 
     16,   0,  16,   0,   0,   0, 
     10,   0,  16,   0,  19,   0, 
      0,   0,   0,   0,   0,   7, 
    242,   0,  16,   0,   4,   0, 
      0,   0,  70,  14,  16,   0, 
      4,   0,   0,   0,  70,  14, 
     16,   0,  16,   0,   0,   0, 
     17,   0,   0,   7,  18,   0, 
     16,   0,  16,   0,   0,   0, 
     70,  14,  16,   0,   4,   0, 
      0,   0,  70,  30,  16,   0, 
      4,   0,   0,   0,  17,   0, 
      0,   7,  34,   0,  16,   0, 
     16,   0,   0,   0,  70,  14, 
     16,   0,   4,   0,   0,   0, 
     70,  30,  16,   0,   5,   0, 
      0,   0,  17,   0,   0,   7, 
     66,   0,  16,   0,  16,   0, 
      0,   0,  70,  14,  16,   0, 
      4,   0,   0,   0,  70,  30, 
     16,   0,   6,   0,   0,   0, 
     17,   0,   0,   7, 130,   0, 
     16,   0,  16,   0,   0,   0, 
     70,  14,  16,   0,   4,   0, 
      0,   0,  70,  30,  16,   0, 
      7,   0,   0,   0,  17,   0, 
      0,   8,  18,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,  16,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
     54,   0,   0,   5,  18,   0, 
     16,   0,   5,   0,   0,   0, 
     42,   0,  16,   0,   3,   0, 
      0,   0,  54,   0,   0,   5, 
     34,   0,  16,   0,   3,   0, 
      0,   0,  42,   0,  16,   0, 
      5,   0,   0,   0,  54,   0, 
      0,   5,  66,   0,  16,   0, 
      3,   0,   0,   0,  26,   0, 
     16,   0,   6,   0,   0,   0, 
     54,   0,   0,   5,  66,   0, 
     16,   0,   5,   0,   0,   0, 
     42,   0,  16,   0,   6,   0, 
      0,   0,  54,   0,   0,   5, 
    130,   0,  16,   0,   3,   0, 
      0,   0,  26,   0,  16,   0, 
      7,   0,   0,   0,  54,   0, 
      0,   5, 130,   0,  16,   0, 
      5,   0,   0,   0,  42,   0, 
     16,   0,   7,   0,   0,   0, 
     54,   0,   0,   5,  18,   0, 
     16,   0,  10,   0,   0,   0, 
     42,   0,  16,   0,   8,   0, 
      0,   0,  54,   0,   0,   5, 
     34,   0,  16,   0,   8,   0, 
      0,   0,  42,   0,  16,   0, 
     10,   0,   0,   0,  54,   0, 
      0,   5,  66,   0,  16,   0, 
      8,   0,   0,   0,  26,   0, 
     16,   0,  11,   0,   0,   0, 
     54,   0,   0,   5,  66,   0, 
     16,   0,  10,   0,   0,   0, 
     42,   0,  16,   0,  11,   0, 
      0,   0,  54,   0,   0,   5, 
    130,   0,  16,   0,   8,   0, 
      0,   0,  26,   0,  16,   0, 
     12,   0,   0,   0,  54,   0, 
      0,   5, 130,   0,  16,   0, 
     10,   0,   0,   0,  42,   0, 
     16,   0,  12,   0,   0,   0, 
      0,   0,   0,   7, 242,   0, 
     16,   0,   4,   0,   0,   0, 
     70,  14,  16,   0,   5,   0, 
      0,   0,  70,  14,  16,   0, 
     10,   0,   0,   0,   0,   0, 
      0,   7, 242,   0,  16,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   8,   0, 
      0,   0,  54,   0,   0,   5, 
     18,   0,  16,   0,  14,   0, 
      0,   0,  42,   0,  16,   0, 
      9,   0,   0,   0,  54,   0, 
      0,   5,  34,   0,  16,   0, 
      9,   0,   0,   0,  42,   0, 
     16,   0,  14,   0,   0,   0, 
     54,   0,   0,   5,  66,   0, 
     16,   0,   9,   0,   0,   0, 
     26,   0,  16,   0,  15,   0, 
      0,   0,  54,   0,   0,   5, 
     66,   0,  16,   0,  14,   0, 
      0,   0,  42,   0,  16,   0, 
     15,   0,   0,   0,  54,   0, 
      0,   5, 130,   0,  16,   0, 
      9,   0,   0,   0,  26,   0, 
     16,   0,   0,   0,   0,   0, 
     54,   0,   0,   5, 130,   0, 
     16,   0,  14,   0,   0,   0, 
     42,   0,  16,   0,   0,   0, 
      0,   0,   0,   0,   0,   7, 
    242,   0,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      4,   0,   0,   0,  70,  14, 
     16,   0,  14,   0,   0,   0, 
      0,   0,   0,   7, 242,   0, 
     16,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70,  14,  16,   0, 
      9,   0,   0,   0,  54,   0, 
      0,   5,  18,   0,  16,   0, 
     17,   0,   0,   0,  42,   0, 
     16,   0,  13,   0,   0,   0, 
     54,   0,   0,   5,  34,   0, 
     16,   0,  13,   0,   0,   0, 
     42,   0,  16,   0,  17,   0, 
      0,   0,  54,   0,   0,   5, 
     66,   0,  16,   0,  13,   0, 
      0,   0,  26,   0,  16,   0, 
     18,   0,   0,   0,  54,   0, 
      0,   5,  66,   0,  16,   0, 
     17,   0,   0,   0,  42,   0, 
     16,   0,  18,   0,   0,   0, 
     54,   0,   0,   5, 130,   0, 
     16,   0,  13,   0,   0,   0, 
     26,   0,  16,   0,  19,   0, 
      0,   0,  54,   0,   0,   5, 
    130,   0,  16,   0,  17,   0, 
      0,   0,  42,   0,  16,   0, 
     19,   0,   0,   0,   0,   0, 
      0,   7, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,  17,   0, 
      0,   0,   0,   0,   0,   7, 
    242,   0,  16,   0,   3,   0, 
      0,   0,  70,  14,  16,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,  13,   0,   0,   0, 
     17,   0,   0,   7,  18,   0, 
     16,   0,   4,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70,  30,  16,   0, 
      4,   0,   0,   0,  17,   0, 
      0,   7,  34,   0,  16,   0, 
      4,   0,   0,   0,  70,  14, 
     16,   0,   3,   0,   0,   0, 
     70,  30,  16,   0,   5,   0, 
      0,   0,  17,   0,   0,   7, 
     66,   0,  16,   0,   4,   0, 
      0,   0,  70,  14,  16,   0, 
      3,   0,   0,   0,  70,  30, 
     16,   0,   6,   0,   0,   0, 
     17,   0,   0,   7, 130,   0, 
     16,   0,   4,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70,  30,  16,   0, 
      7,   0,   0,   0,  17,   0, 
      0,   8,  34,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   4,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
     17,   0,   0,   7,  18,   0, 
     16,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  70,  30,  16,   0, 
      4,   0,   0,   0,  17,   0, 
      0,   7,  34,   0,  16,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70,  30,  16,   0,   5,   0, 
      0,   0,  17,   0,   0,   7, 
     66,   0,  16,   0,   3,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  70,  30, 
     16,   0,   6,   0,   0,   0, 
     17,   0,   0,   7, 130,   0, 
     16,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  70,  30,  16,   0, 
      7,   0,   0,   0,  17,   0, 
      0,   8,  66,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   3,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
     54,   0,   0,   5, 114,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  18,  16,   0,   0,   0, 
      0,   0,  54,   0,   0,   5, 
    130,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0, 128,  63,  17,   0, 
      0,   7, 130,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  17,   0,   0,   8, 
     18,   0,  16,   0,   5,   0, 
      0,   0,  70,  14,  16,   0, 
     16,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  17,   0, 
      0,   8,  34,   0,  16,   0, 
      5,   0,   0,   0,  70,  14, 
     16,   0,   4,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     17,   0,   0,   8,  66,   0, 
     16,   0,   5,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  17,   0,   0,   8, 
    130,   0,  16,   0,   5,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  17,   0, 
      0,   7,  18,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   5,   0, 
      0,   0,  16,   0,   0,   7, 
     18,  32,  16,   0,   1,   0, 
      0,   0,  70,  18,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   5,   0,   0,   0, 
     17,   0,   0,   8, 130,   0, 
     16,   0,   5,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,  17,   0,   0,   8, 
    130,   0,  16,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,  17,   0, 
      0,   8,  18,   0,  16,   0, 
      5,   0,   0,   0,  70,  14, 
     16,   0,  16,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
     17,   0,   0,   8,  18,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,  16,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,  17,   0,   0,   8, 
     34,   0,  16,   0,   5,   0, 
      0,   0,  70,  14,  16,   0, 
      4,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  17,   0, 
      0,   8,  34,   0,  16,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   4,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
     17,   0,   0,   8,  66,   0, 
     16,   0,   5,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,  17,   0,   0,   8, 
     66,   0,  16,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      3,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,  17,   0, 
      0,   7,  34,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   5,   0, 
      0,   0,  16,   0,   0,   7, 
     34,  32,  16,   0,   1,   0, 
      0,   0,  70,  18,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   5,   0,   0,   0, 
     17,   0,   0,   7,  66,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,  16,   0, 
      0,   7,  66,  32,  16,   0, 
      1,   0,   0,   0,  70,  18, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,  17,   0,   0,   8, 
     18,  32,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      4,   0,   0,   0,  17,   0, 
      0,   8,  34,  32,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   5,   0,   0,   0, 
     17,   0,   0,   8,  66,  32, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   6,   0, 
      0,   0,  17,   0,   0,   8, 
    130,  32,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      7,   0,   0,   0,  62,   0, 
      0,   1,  83,  84,  65,  84, 
    148,   0,   0,   0, 132,   0, 
      0,   0,  20,   0,   0,   0, 
      0,   0,   0,   0,  26,   0, 
      0,   0,  72,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  58,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0
};
