
undefined8
FUN_fffffff00a27b7ac
          (long param_1,ulong *param_2,ulong param_3,undefined8 param_4,ulong param_5,long param_6,
          ulong param_7,ulong param_8,uint *param_9,uint *param_10,uint param_11)

{
  ulong uVar1;
  uint uVar2;
  byte bVar3;
  long lVar4;
  ulong uVar5;
  long *plVar6;
  long lVar7;
  long lVar8;
  ulong uVar9;
  undefined4 *puVar10;
  ulong uVar11;
  ulong uVar12;
  ulong uVar13;
  long lVar14;
  ulong uVar15;
  uint uVar16;
  undefined8 uVar17;
  ulong uVar18;
  ulong local_138;
  undefined1 auStack_130 [8];
  ulong local_128;
  long *local_120;
  undefined8 uStack_118;
  undefined8 local_110;
  undefined8 uStack_108;
  undefined8 local_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 local_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 local_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  long local_a0;
  long *local_98;
  long *local_90;
  uint local_88;
  uint local_84;
  long local_80;
  undefined8 local_78;
  undefined8 local_70;
  
  local_78 = 0;
  local_80 = 0;
  local_98 = &local_a0;
  local_a0 = 0;
  local_90 = (long *)0x0;
  uStack_b8 = 0;
  local_c0 = 0;
  uStack_a8 = 0;
  uStack_b0 = 0;
  uStack_d8 = 0;
  local_e0 = 0;
  uStack_c8 = 0;
  uStack_d0 = 0;
  uStack_f8 = 0;
  local_100 = 0;
  uStack_e8 = 0;
  uStack_f0 = 0;
  uVar17 = 4;
  uStack_108 = 0;
  local_110 = 0;
  local_70 = param_5;
  if (((param_1 != 0) && (param_6 != 0)) && (param_11 < 3)) {
    bVar3 = *(byte *)(param_1 + 0x2c);
    uVar12 = *param_2;
    local_84 = *param_9;
    uVar16 = *param_10;
    if (((local_84 < 8) && (local_88 = uVar16, uVar16 < 8)) &&
       (((local_84 & (uVar16 ^ 0xffffffff)) == 0 && (param_3 != 0)))) {
      uVar16 = -1 << (ulong)(*(byte *)(param_6 + 0x2c) & 0x1f);
      uVar18 = (ulong)~uVar16;
      uVar9 = param_7 & (uVar18 ^ 0xffffffffffffffff);
      uVar15 = uVar9;
      if ((param_5 & 0x100000) != 0) {
        uVar15 = param_7;
      }
      if ((!CARRY8(uVar15,param_3)) &&
         (uVar11 = uVar15 + param_3 + uVar18 & ~uVar18, uVar15 = uVar11 - uVar9,
         uVar9 <= uVar11 && uVar15 != 0)) {
        if ((param_5 & 1) == 0) {
          local_70 = param_5 & 0xffffffffffffbffe;
        }
        uVar5 = local_70;
        uVar11 = uVar15;
        if ((local_70 & 0x100000) != 0) {
          uVar11 = param_3;
        }
        if (((int)param_8 != 0) || (((uint)local_70 >> 6 & 1) == 0)) {
          uVar1 = 0x2000000000000;
          if (param_6 != param_1) {
            uVar1 = 0;
          }
          local_70 = local_70 & 0xfffdffffffffffff | uVar1;
          uVar17 = FUN_fffffff00a273c00
                             (param_6,uVar9,uVar15,param_8,&local_90,&local_84,&local_88,param_11,
                              local_70);
          if ((int)uVar17 == 0) {
            uVar13 = -1L << ((ulong)bVar3 & 0x3f);
            uVar9 = param_7 & uVar18 & (long)(uVar5 << 0x2b) >> 0x3f;
            if (param_6 == param_1) {
              local_70 = uVar5 & 0x8000000000000000 |
                         uVar5 & 0xffdffffffffffff | uVar1 |
                         (ulong)(*(byte *)((long)local_90 + 0x2f) & 7) << 0x3c;
              plVar6 = local_120;
              local_120 = local_90;
            }
            else {
              FUN_fffffff00a278a7c(&local_70,param_1,uVar15,param_4);
              plVar6 = local_120;
              local_120 = local_90;
            }
            local_90 = local_120;
            if (uVar16 != (uint)uVar13) {
              local_138 = 0;
              local_128 = 0;
              uVar17 = FUN_fffffff00a278bdc
                                 (local_120,uVar9,uVar11,param_1,param_8 & 0xffffffff,&local_120,
                                  &local_128,auStack_130,&local_138);
              if ((int)uVar17 != 0) goto LAB_fffffff00a27b910;
              uVar15 = 0;
              if (local_138 <= uVar9) {
                uVar15 = uVar9 - local_138;
              }
              if (local_138 != 0) {
                uVar9 = uVar15;
              }
              uVar9 = uVar9 + local_128;
              uVar15 = local_120[4];
              plVar6 = local_120;
            }
            local_120 = plVar6;
            uVar15 = uVar15 + ~(uint)uVar13 & uVar13;
            if (uVar15 == 0) {
              uVar17 = 4;
            }
            else {
              local_128 = local_128 & 0xffffffff00000000;
              local_120 = (long *)0x0;
              uStack_118 = 0;
              lVar8 = tpidr_el1;
              *(int *)(lVar8 + 0x214) = *(int *)(lVar8 + 0x214) + 1;
              if (((*(ulong *)(param_1 + 0x38) & 0xffffffff0001ffff) == 0x10000) &&
                 (*(int *)(param_1 + 0x3c) == 0)) {
                *(int *)(param_1 + 0x3c) = 2;
              }
              else {
                FUN_fffffff00a1ba0b4(param_1 + 0x30,lVar8,0,param_4);
              }
              uVar18 = local_70;
              *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(lVar8 + 0x4e0);
              uVar16 = (uint)local_70;
              if ((local_70 & 1) == 0) {
                uVar17 = FUN_fffffff00a275a10
                                   (param_1,uVar12 & uVar13,uVar15,param_4,local_70,&local_80);
              }
              else {
                uVar17 = FUN_fffffff00a276b44
                                   (param_1,uVar12 & uVar13,uVar15,param_4,local_70,&local_80,
                                    &local_110,&local_128);
              }
              plVar6 = local_90;
              if ((int)uVar17 == 0) {
                lVar14 = *local_90;
                while (lVar4 = lVar14, lVar4 != 0) {
                  lVar14 = *(long *)(lVar4 + 8);
                  if ((uVar18 >> 0x2a & 1) != 0) {
                    uVar2 = *(uint *)(lVar4 + 0x38);
                    if (((uVar2 >> 0x10 & 1) == 0) ||
                       ((((uVar2 >> 10 & 1) != 0 && (DAT_fffffff007bfce78 != (byte *)0x0)) &&
                        ((*DAT_fffffff007bfce78 & 1) != 0)))) {
                      *(uint *)(lVar4 + 0x38) = uVar2 | 0x200;
                    }
                    else {
                      uVar17 = FUN_fffffff00a22d63c(lVar8);
                      lVar7 = FUN_fffffff00a22cb94();
                      if (lVar7 != 0) {
                        FUN_fffffff00a22cb94(uVar17);
                      }
                    }
                  }
                  if ((uVar16 >> 5 & 1) != 0) {
                    local_88 = 1;
                    local_84 = 1;
                    *(uint *)(lVar4 + 0x38) = *(uint *)(lVar4 + 0x38) & 0xffdff08f | 0x200110;
                  }
                  if ((uVar16 >> 6 & 1) != 0) {
                    puVar10 = (undefined4 *)(*(ulong *)(lVar4 + 0x28) & 0xfffffffffffffffc);
                    if ((*(ulong *)(lVar4 + 0x28) & 3) != 0) {
                      puVar10 = &DAT_fffffff00ad5a300;
                    }
                    if ((puVar10 == (undefined4 *)0x0) ||
                       ((*(byte *)((long)puVar10 + 0x75) >> 4 & 1) != 0)) {
                      *(uint *)(lVar4 + 0x38) = *(uint *)(lVar4 + 0x38) | 0x400000;
                    }
                  }
                  if (((uVar18 >> 0x2a & 1) == 0) && ((*(uint *)(lVar4 + 0x38) >> 0x12 & 1) != 0)) {
                    FUN_fffffff00a87b040
                              (&MACH_HEADER,&DAT_fffffff00ad38ab8,0,
                               "%s: downgrading VM entry [%p, %p) from JIT to non-JIT");
                    uVar2 = *(uint *)(lVar4 + 0x38);
                    *(uint *)(lVar4 + 0x38) = uVar2 & 0xfffbfbbf;
                    if ((uVar18 >> 0x2b & 1) != 0) {
                      local_84 = local_84 & uVar2 >> 4 & 3;
                      local_88 = local_88 & uVar2 >> 8 & 0xb;
                    }
                  }
                }
                uVar17 = FUN_fffffff00a27a8a4
                                   (param_1,plVar6,&local_110,&local_120,
                                    uVar18 >> 2 & 2 | uVar18 >> 0x34 & 1 | uVar18 >> 0x2a & 0xc |
                                    (uVar18 & 1) << 4 | uVar18 >> 9 & 0x20 | uVar18 >> 0x10 & 0x40 |
                                    0x800);
                if ((int)uVar17 == 0) {
                  if ((uVar16 >> 0xe & 1) != 0) {
                    FUN_fffffff00a2775a8
                              (param_1,&local_110,local_128 & 0xffffffff,&local_a0,&local_80);
                  }
                  puVar10 = (undefined4 *)*plVar6;
                  lVar14 = local_80;
                  while (puVar10 != (undefined4 *)0x0) {
                    FUN_fffffff00a2909e4(plVar6,puVar10);
                    lVar4 = local_80;
                    lVar14 = (lVar14 << 1) >> 1;
                    *(long *)(puVar10 + 6) = lVar14 + *(long *)(puVar10 + 6);
                    *(long *)(puVar10 + 4) = lVar14 + *(long *)(puVar10 + 4);
                    *puVar10 = 0x30000;
                    *(int *)(lVar8 + 0x214) = *(int *)(lVar8 + 0x214) + 1;
                    uVar17 = FUN_fffffff00a290a98(param_1,puVar10,local_80,local_78,uVar18);
                    FUN_fffffff00a2d9500(uVar17,puVar10);
                    lVar14 = lVar4;
                    puVar10 = (undefined4 *)*plVar6;
                  }
                  *(long *)(param_1 + 0x60) = *(long *)(param_1 + 0x60) - (long)local_120;
                  FUN_fffffff00a1ba72c(param_1 + 0x30);
                  uVar17 = 0;
                  *param_2 = (uVar9 & (long)(uVar18 << 0x2b) >> 0x3f) + ((lVar14 << 1) >> 1);
                  *param_9 = local_84;
                  *param_10 = local_88;
                  goto LAB_fffffff00a27b910;
                }
                FUN_fffffff00a28fa24(param_1,local_80,local_78);
              }
              FUN_fffffff00a1ba72c(param_1 + 0x30);
            }
          }
        }
      }
    }
  }
LAB_fffffff00a27b910:
  if (((local_70._1_1_ >> 6 & 1) != 0) && (local_a0 != 0)) {
    do {
      lVar8 = *(long *)(local_a0 + 8);
      if (lVar8 == 0) {
        local_98 = &local_a0;
      }
      *(undefined8 *)(local_a0 + 8) = 0;
      local_a0 = lVar8;
      FUN_fffffff00a271ef0(0);
    } while (local_a0 != 0);
  }
  if (local_90 != (long *)0x0) {
    FUN_fffffff00a274900();
  }
  return uVar17;
}

