
undefined8
FUN_fffffff00a2b7fd4
          (long param_1,ulong *param_2,ulong param_3,undefined8 param_4,ulong param_5,long param_6,
          ulong param_7,ulong param_8,uint *param_9,uint *param_10,uint param_11)

{
  ulong uVar1;
  uint uVar2;
  byte bVar3;
  long *plVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  uint uVar8;
  long lVar9;
  ulong uVar10;
  undefined4 *puVar11;
  ulong uVar12;
  ulong uVar13;
  long lVar14;
  ulong uVar15;
  uint uVar16;
  undefined8 uVar17;
  ulong uVar18;
  ulong uVar19;
  ulong local_138;
  undefined1 auStack_130 [8];
  ulong local_128;
  long *local_120;
  undefined8 uStack_118;
  long local_110;
  undefined8 uStack_108;
  undefined8 local_100;
  long lStack_f8;
  undefined8 uStack_f0;
  uint local_e8;
  ushort local_e4;
  undefined2 uStack_e2;
  undefined8 uStack_e0;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 local_b0;
  undefined4 uStack_ac;
  undefined4 local_a8;
  undefined4 uStack_a4;
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
  uStack_b4 = 0;
  uStack_c0 = 0;
  uStack_bc = 0;
  local_a8 = 0;
  uStack_a4 = 0;
  local_b0 = 0;
  uStack_ac = 0;
  uStack_d8 = 0;
  uStack_d4 = 0;
  uStack_e0._0_4_ = 0;
  uStack_e0._4_4_ = 0;
  uStack_c8 = 0;
  uStack_c4 = 0;
  uStack_d0 = 0;
  uStack_cc = 0;
  lStack_f8 = 0;
  local_100 = 0;
  local_e8 = 0;
  local_e4 = 0;
  uStack_e2 = 0;
  uStack_f0 = 0;
  uVar17 = 4;
  uStack_108 = 0;
  local_110 = 0;
  local_70 = param_5;
  if (((param_1 == 0) || (param_6 == 0)) || (2 < param_11)) goto LAB_fffffff00a2b82c4;
  bVar3 = *(byte *)(param_1 + 0x2c);
  uVar18 = *param_2;
  local_84 = *param_9;
  uVar16 = *param_10;
  if (((7 < local_84) || (local_88 = uVar16, 7 < uVar16)) ||
     (((local_84 & (uVar16 ^ 0xffffffff)) != 0 || (param_3 == 0)))) goto LAB_fffffff00a2b82c4;
  uVar8 = -1 << (ulong)(*(byte *)(param_6 + 0x2c) & 0x1f);
  uVar19 = (ulong)~uVar8;
  uVar10 = param_7 & (uVar19 ^ 0xffffffffffffffff);
  uVar15 = uVar10;
  if ((param_5 & 0x100000) != 0) {
    uVar15 = param_7;
  }
  if ((CARRY8(uVar15,param_3)) ||
     (uVar12 = uVar15 + param_3 + uVar19 & ~uVar19, uVar15 = uVar12 - uVar10,
     uVar12 < uVar10 || uVar15 == 0)) goto LAB_fffffff00a2b82c4;
  if ((param_5 & 1) == 0) {
    local_70 = param_5 & 0xffffffffffffbffe;
  }
  uVar6 = local_70;
  uVar12 = uVar15;
  if ((local_70 & 0x100000) != 0) {
    uVar12 = param_3;
  }
  if ((((int)param_8 == 0) && (((uint)local_70 >> 6 & 1) != 0)) ||
     ((((uint)local_70 >> 8 & 1) != 0 &&
      ((((local_70 >> 0x2b & 1) != 0 || (uVar17 = 2, 1 < local_84)) || (1 < uVar16))))))
  goto LAB_fffffff00a2b82c4;
  uVar1 = 0x2000000000000;
  if (param_6 != param_1) {
    uVar1 = 0;
  }
  local_70 = local_70 & 0xfffdffffffffffff | uVar1;
  uVar17 = FUN_fffffff00a2b042c
                     (param_6,uVar10,uVar15,param_8,&local_90,&local_84,&local_88,param_11,local_70)
  ;
  if ((int)uVar17 != 0) goto LAB_fffffff00a2b82c4;
  uVar13 = -1L << ((ulong)bVar3 & 0x3f);
  uVar10 = param_7 & uVar19 & (long)(uVar6 << 0x2b) >> 0x3f;
  uVar16 = (uint)uVar13;
  if (param_6 == param_1) {
    local_70 = uVar6 & 0x8000000000000000 |
               uVar6 & 0xffdffffffffffff | uVar1 |
               (ulong)(*(byte *)((long)local_90 + 0x2f) & 7) << 0x3c;
    if (uVar8 != uVar16) goto LAB_fffffff00a2b81b4;
  }
  else {
    FUN_fffffff00a2b52a4(&local_70,param_1,uVar15,param_4);
    if (uVar8 != uVar16) {
LAB_fffffff00a2b81b4:
      local_138 = 0;
      local_128 = 0;
      local_120 = local_90;
      uVar17 = FUN_fffffff00a2b5404
                         (local_90,uVar10,uVar12,param_1,param_8 & 0xffffffff,&local_120,&local_128,
                          auStack_130,&local_138);
      if ((int)uVar17 != 0) {
        goto LAB_fffffff00a2b82c4;
      }
      uVar15 = 0;
      if (local_138 <= uVar10) {
        uVar15 = uVar10 - local_138;
      }
      if (local_138 != 0) {
        uVar10 = uVar15;
      }
      uVar10 = uVar10 + local_128;
      uVar15 = local_120[4];
    }
  }
  uVar15 = uVar15 + ~uVar16 & uVar13;
  if (uVar15 == 0) {
    uVar17 = 4;
  }
  else {
    local_128 = local_128 & 0xffffffff00000000;
    local_120 = (long *)0x0;
    uStack_118 = 0;
    lVar9 = tpidr_el1;
    *(int *)(lVar9 + 0x214) = *(int *)(lVar9 + 0x214) + 1;
    if (((*(ulong *)(param_1 + 0x38) & 0xffffffff0001ffff) == 0x10000) &&
       (*(int *)(param_1 + 0x3c) == 0)) {
      *(int *)(param_1 + 0x3c) = 2;
    }
    else {
      FUN_fffffff00a1f638c(param_1 + 0x30,lVar9,0,param_4);
    }
    uVar19 = local_70;
    *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(lVar9 + 0x4e0);
    uVar16 = (uint)local_70;
    if ((local_70 & 1) == 0) {
      uVar17 = FUN_fffffff00a2b223c(param_1,uVar18 & uVar13,uVar15,param_4,local_70,&local_80);
    }
    else {
      uVar17 = FUN_fffffff00a2b336c
                         (param_1,uVar18 & uVar13,uVar15,param_4,local_70,&local_80,&local_110,
                          &local_128);
    }
    plVar4 = local_90;
    if ((int)uVar17 == 0) {
      lVar14 = *local_90;
      while (lVar5 = lVar14, lVar5 != 0) {
        lVar14 = *(long *)(lVar5 + 8);
        if ((uVar19 >> 0x2a & 1) != 0) {
          uVar8 = *(uint *)(lVar5 + 0x38);
          if (((uVar8 >> 0x10 & 1) == 0) ||
             ((((uVar8 >> 10 & 1) != 0 && (DAT_fffffff007c08ec8 != (byte *)0x0)) &&
              ((*DAT_fffffff007c08ec8 & 1) != 0)))) {
            *(uint *)(lVar5 + 0x38) = uVar8 | 0x200;
          }
          else {
            uVar17 = FUN_fffffff00a269a54(lVar9);
            lVar7 = FUN_fffffff00a268fac();
            if (lVar7 != 0) {
              FUN_fffffff00a268fac(uVar17);
            }
          }
        }
        if ((uVar16 >> 5 & 1) != 0) {
          local_88 = 1;
          local_84 = 1;
          *(uint *)(lVar5 + 0x38) = *(uint *)(lVar5 + 0x38) & 0xffdff08f | 0x200110;
        }
        if ((uVar16 >> 6 & 1) != 0) {
          puVar11 = (undefined4 *)(*(ulong *)(lVar5 + 0x28) & 0xfffffffffffffffc);
          if ((*(ulong *)(lVar5 + 0x28) & 3) != 0) {
            puVar11 = &DAT_fffffff00ad9b300;
          }
          if ((puVar11 == (undefined4 *)0x0) || ((*(byte *)((long)puVar11 + 0x75) >> 4 & 1) != 0)) {
            *(uint *)(lVar5 + 0x38) = *(uint *)(lVar5 + 0x38) | 0x400000;
          }
        }
        uVar8 = *(uint *)(lVar5 + 0x38);
        if (((uVar19 >> 0x2a & 1) == 0) && ((uVar8 >> 0x12 & 1) != 0)) {
          FUN_fffffff00a8bae98
                    (&MACH_HEADER,&DAT_fffffff00ad78b98,0,
                     "%s: downgrading VM entry [%p, %p) from JIT to non-JIT");
          uVar2 = *(uint *)(lVar5 + 0x38);
          uVar8 = uVar2 & 0xfffbfbbf;
          *(uint *)(lVar5 + 0x38) = uVar8;
          if ((uVar19 >> 0x2b & 1) != 0) {
            local_84 = local_84 & uVar2 >> 4 & 3;
            local_88 = local_88 & uVar2 >> 8 & 0xb;
          }
        }
        if (((uVar16 >> 8 & 1) != 0) && ((uVar8 >> 7 & 1) != 0)) {
          *(uint *)(lVar5 + 0x38) = uVar8 & 0xfffeff7f;
        }
      }
      uVar17 = FUN_fffffff00a2b70cc
                         (param_1,plVar4,&local_110,&local_120,
                          uVar19 >> 2 & 2 | uVar19 >> 0x34 & 1 | uVar19 >> 0x2a & 0xc |
                          (uVar19 & 1) << 4 | uVar19 >> 9 & 0x20 | uVar19 >> 0x10 & 0x40 | 0x800);
      if ((int)uVar17 == 0) {
        if ((uVar16 >> 0xe & 1) != 0) {
          FUN_fffffff00a2b3dd0(param_1,&local_110,local_128 & 0xffffffff,&local_a0,&local_80);
        }
        puVar11 = (undefined4 *)*plVar4;
        lVar14 = local_80;
        while (puVar11 != (undefined4 *)0x0) {
          FUN_fffffff00a2cd31c(plVar4,puVar11);
          lVar5 = local_80;
          lVar14 = (lVar14 << 1) >> 1;
          *(long *)(puVar11 + 6) = lVar14 + *(long *)(puVar11 + 6);
          *(long *)(puVar11 + 4) = lVar14 + *(long *)(puVar11 + 4);
          *puVar11 = 0x30000;
          *(int *)(lVar9 + 0x214) = *(int *)(lVar9 + 0x214) + 1;
          uVar17 = FUN_fffffff00a2cd3d0(param_1,puVar11,local_80,local_78,uVar19);
          FUN_fffffff00a31603c(uVar17,puVar11);
          lVar14 = lVar5;
          puVar11 = (undefined4 *)*plVar4;
        }
        *(long *)(param_1 + 0x60) = *(long *)(param_1 + 0x60) - (long)local_120;
        FUN_fffffff00a1f6a04(param_1 + 0x30);
        uVar17 = 0;
        *param_2 = (uVar10 & (long)(uVar19 << 0x2b) >> 0x3f) + ((lVar14 << 1) >> 1);
        *param_9 = local_84;
        *param_10 = local_88;
      }
      else {
        FUN_fffffff00a2cc35c(param_1,local_80,local_78);
        FUN_fffffff00a1f6a04(param_1 + 0x30);
        if ((uVar16 >> 0xe & 1) != 0) {
          *(undefined8 *)(lVar9 + 0x220) = 0;
          if ((local_e4 & 0xc) == 8) {
            if (((byte)local_e8 >> 2 & 1) == 0) {
              local_110 = CONCAT44(uStack_c4,uStack_c8);
            }
            else {
              uStack_e0 = CONCAT44(uStack_ac,local_b0) +
                          CONCAT44(uStack_e0._4_4_,(undefined4)uStack_e0);
              local_110 = local_110 + CONCAT44(uStack_ac,local_b0);
            }
            lStack_f8 = CONCAT44(uStack_a4,local_a8);
            local_100 = CONCAT44(uStack_b4,uStack_b8);
            uStack_108 = CONCAT44(uStack_bc,uStack_c0);
            local_e4 = local_e4 & 0xfff3;
            local_b0 = 0;
            uStack_ac = 0;
            local_a8 = 0;
            uStack_a4 = 0;
          }
          if ((local_e8 >> 2 & 1) == 0) {
            FUN_fffffff00a31a908(&local_110);
          }
          else if ((lStack_f8 != 0) &&
                  (((~*(uint *)(lStack_f8 + 0x28) & 3) != 0 ||
                   ((*(uint *)(lStack_f8 + 0x24) & 1) == 0)))) {
            FUN_fffffff00a31603c();
          }
          local_100 = 0;
          lStack_f8 = 0;
          uStack_e0._4_4_ = 0;
          uStack_d8 = 0;
          local_e4 = 0;
          uStack_e2 = 0;
          uStack_e0._0_4_ = 0;
          uStack_cc = 0;
          uStack_c8 = 0;
          uStack_d4 = 0;
          uStack_d0 = 0;
          uStack_bc = 0;
          uStack_b8 = 0;
          uStack_c4 = 0;
          uStack_c0 = 0;
          uStack_ac = 0;
          local_a8 = 0;
          uStack_b4 = 0;
          local_b0 = 0;
          uStack_a4 = 0;
        }
      }
    }
    else {
      FUN_fffffff00a1f6a04(param_1 + 0x30);
    }
  }
LAB_fffffff00a2b82c4:
  if (((local_70._1_1_ >> 6 & 1) != 0) && (local_a0 != 0)) {
    do {
      lVar9 = *(long *)(local_a0 + 8);
      if (lVar9 == 0) {
        local_98 = &local_a0;
      }
      *(undefined8 *)(local_a0 + 8) = 0;
      local_a0 = lVar9;
      FUN_fffffff00a2ae710(0);
    } while (local_a0 != 0);
  }
  if (local_90 != (long *)0x0) {
    FUN_fffffff00a2b112c();
  }
  return uVar17;
}

