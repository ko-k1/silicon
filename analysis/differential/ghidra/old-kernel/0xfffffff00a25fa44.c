
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_fffffff00a25fa44
          (uint *param_1,ulong param_2,ulong param_3,undefined8 param_4,undefined8 param_5,
          undefined8 param_6,uint param_7,undefined8 param_8)

{
  long *plVar1;
  uint *puVar2;
  byte bVar3;
  ushort uVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  bool bVar22;
  bool bVar23;
  int iVar24;
  int iVar25;
  long lVar26;
  long *plVar27;
  undefined8 uVar28;
  ulong uVar29;
  ulong uVar30;
  undefined8 uVar31;
  ulong uVar32;
  uint uVar33;
  uint uVar34;
  ulong uVar35;
  uint uVar36;
  uint uVar37;
  ulong uVar38;
  long lVar39;
  ulong uVar40;
  uint *puVar41;
  ulong uVar42;
  long *plVar43;
  undefined4 in_wzr;
  undefined1 auVar44 [16];
  undefined1 auVar45 [16];
  undefined1 auVar46 [16];
  undefined1 auVar47 [16];
  undefined1 auVar48 [16];
  undefined1 auVar49 [16];
  undefined1 auVar50 [16];
  undefined1 auVar51 [16];
  undefined1 auVar52 [16];
  undefined1 auVar53 [16];
  undefined1 auVar54 [16];
  undefined1 auVar55 [16];
  undefined1 auVar56 [16];
  ulong in_stack_fffffffffffffe00;
  undefined4 local_1d4;
  int local_1a8;
  uint local_1a4;
  ulong local_1a0;
  long *local_198;
  ulong local_190;
  long local_180;
  long lStack_178;
  undefined8 local_170;
  ulong uStack_168;
  ulong uStack_160;
  undefined8 local_158;
  undefined4 local_14c;
  long local_148;
  long local_140;
  undefined4 local_134;
  ulong local_130 [26];
  
  local_130[0x18] = DAT_fffffff00acd0000;
  local_130[0x15] = 0;
  local_130[0x14] = 0;
  local_130[0x17] = 0;
  local_130[0x16] = 0;
  local_130[0x11] = 0;
  local_130[0x10] = 0;
  local_130[0x13] = 0;
  local_130[0x12] = 0;
  local_130[0xd] = 0;
  local_130[0xc] = 0;
  local_130[0xf] = 0;
  local_130[0xe] = 0;
  local_130[9] = 0;
  local_130[8] = 0;
  local_130[0xb] = 0;
  local_130[10] = 0;
  local_130[5] = 0;
  local_130[4] = 0;
  local_130[7] = 0;
  local_130[6] = 0;
  bVar22 = (param_7 & 8) != 0;
  bVar23 = (param_7 & 3) == 1;
  local_130[1] = 0;
  local_130[0] = 0;
  local_130[3] = 0;
  local_130[2] = 0;
  if (((param_7 >> 4 & 1) != 0) || (bVar22 || bVar23)) {
    puVar41 = *(uint **)(param_1 + 0xe);
    if (puVar41 != (uint *)0x0) {
      uVar37 = 1;
      do {
        iVar24 = FUN_fffffff00a29e560(puVar41);
        FUN_fffffff00a1bad04(param_1 + 2);
        if (iVar24 != 0) {
          if (puVar41[10] + 0xf0000001 < 0xf0000002) {
                    /* WARNING: Subroutine does not return */
            FUN_fffffff00aa00834(puVar41 + 10);
          }
          puVar41[10] = puVar41[10] + 1;
          break;
        }
        uVar36 = uVar37;
        if (0x1e < uVar37) {
          uVar36 = 0x1f;
        }
        (&DAT_fffffff00acd3da0)[uVar36] = (&DAT_fffffff00acd3da0)[uVar36] + 1;
        uVar36 = uVar37;
        if (6 < uVar37) {
          uVar36 = 7;
        }
        FUN_fffffff00a1d6f28(FUN_fffffff00a1b6f8c,0,(&DAT_fffffff00acac410)[uVar36],1000);
        FUN_fffffff00a1d7b28(0,0,0);
        FUN_fffffff00a298e80(param_1);
        puVar41 = *(uint **)(param_1 + 0xe);
        uVar37 = uVar37 + 1;
      } while (puVar41 != (uint *)0x0);
    }
  }
  else {
    puVar41 = (uint *)0x0;
  }
  if (((param_7 >> 4 & 1) != 0) || (puVar41 != (uint *)0x0 && (bVar22 || bVar23))) {
    local_134 = 0;
    local_148 = 0;
    local_140 = 0;
    local_14c = 0;
    lStack_178 = 0;
    local_180 = 0;
    if (puVar41 == (uint *)0x0) {
      uVar35 = param_3 + param_2;
      uVar42 = param_2;
      puVar41 = param_1;
    }
    else {
      uVar35 = *(ulong *)(puVar41 + 0x16);
      uVar40 = 0;
      if (uVar35 - param_2 <= param_3) {
        uVar40 = param_3 - (uVar35 - param_2);
      }
      if (uVar35 <= param_2) {
        uVar40 = param_3;
      }
      uVar38 = *(ulong *)(puVar41 + 6);
      uVar42 = 0;
      if (uVar35 <= param_2) {
        uVar42 = param_2 - uVar35;
      }
      if (uVar38 <= uVar42) {
        uVar42 = uVar38;
      }
      uVar35 = uVar38 - uVar42;
      if (uVar40 + uVar42 <= uVar38) {
        uVar35 = uVar40;
      }
      uVar35 = uVar35 + uVar42;
    }
    local_170 = 2;
    uStack_168 = uVar42;
    uStack_160 = uVar35;
    local_158 = 2;
    uVar37 = (ushort)puVar41[0x1b] + 1;
    *(short *)(puVar41 + 0x1b) = (short)uVar37;
    if (uVar37 >> 0x10 != 0) {
LAB_fffffff00a2609bc:
                    /* WARNING: Subroutine does not return */
      FUN_fffffff00a9ebcbc("vm_object_paging_begin(%p): overflow\n @%s:%d");
    }
    if (uVar42 < uVar35) {
LAB_fffffff00a25fc8c:
      do {
        local_134 = 3;
        local_140 = 0;
        in_stack_fffffffffffffe00 = in_stack_fffffffffffffe00 & 0xffffffff00000000;
        lStack_178 = uVar35 - uVar42;
        lVar26 = FUN_fffffff00a267678
                           (puVar41,uVar42,3,0,0,&local_134,&local_140,&local_148,0,&local_14c,
                            in_stack_fffffffffffffe00,&local_180,0);
        iVar24 = (int)lVar26;
        if (iVar24 < 3) {
          if (iVar24 == 1) {
            local_134 = 3;
            FUN_fffffff00a298e80(puVar41);
            uVar37 = (ushort)puVar41[0x1b] + 1;
            *(short *)(puVar41 + 0x1b) = (short)uVar37;
          }
          else {
            if (iVar24 != 2) {
              if (iVar24 != 0) goto LAB_fffffff00a2609c8;
              if (local_148 != 0) {
                lVar26 = 0;
                if (*(uint *)(local_140 + 0x1c) != 0) {
                  lVar26 = (ulong)*(uint *)(local_140 + 0x1c) * 0x40 + -0x2400000000;
                }
                FUN_fffffff00a269c98(lVar26);
                lVar26 = FUN_fffffff00a298e80(puVar41);
                uVar37 = (ushort)puVar41[0x1b] + 1;
                *(short *)(puVar41 + 0x1b) = (short)uVar37;
                if (uVar37 >> 0x10 != 0) goto LAB_fffffff00a2609bc;
              }
              if ((1L << (*(byte *)(local_140 + 0x2a) & 0xf) & 0x3c60U) == 0) {
                lVar39 = tpidr_el1;
                *(int *)(lVar39 + 0x1b8) = *(int *)(lVar39 + 0x1b8) + 1;
                if (_DAT_fffffff00ad0d0c8 == 0) {
                  _DAT_fffffff00ad0d0c8 = (ulong)*(uint *)(lVar39 + 0x4e0) | 0x30000000;
                }
                else {
                  FUN_fffffff00a1b6050(&DAT_fffffff00ad0d0c0,lVar39,1);
                }
                lVar26 = local_140;
                if ((1L << (*(byte *)(local_140 + 0x2a) & 0xf) & 0x3c60U) == 0) {
                  lVar26 = FUN_fffffff00a2bcebc(local_140,1);
                }
                if (DAT_fffffff00ad0d0c8 == *(int *)(lVar39 + 0x4e0)) {
                  _DAT_fffffff00ad0d0c8 = CONCAT44(DAT_fffffff00ad0d0c8_4,in_wzr);
                }
                else {
                  lVar26 = FUN_fffffff00a1b6b90(&DAT_fffffff00ad0d0c0,lVar39);
                }
              }
              FUN_fffffff00a29d5f8(lVar26,local_140);
              goto LAB_fffffff00a25fc80;
            }
            local_134 = 3;
            FUN_fffffff00a298e80(puVar41);
            uVar37 = (ushort)puVar41[0x1b] + 1;
            *(short *)(puVar41 + 0x1b) = (short)uVar37;
          }
        }
        else {
          if (iVar24 != 3) goto LAB_fffffff00a25fd54;
          FUN_fffffff00a2c04e8(0);
          local_134 = 3;
          FUN_fffffff00a298e80(puVar41);
          uVar37 = (ushort)puVar41[0x1b] + 1;
          *(short *)(puVar41 + 0x1b) = (short)uVar37;
        }
        if (uVar37 >> 0x10 != 0) goto LAB_fffffff00a2609bc;
      } while( true );
    }
    goto LAB_fffffff00a25fe88;
  }
LAB_fffffff00a25ff64:
  if ((param_7 & 0x18) == 0) {
    if (puVar41 != (uint *)0x0 && puVar41 != param_1) {
      FUN_fffffff00a1bad04(puVar41 + 2);
      FUN_fffffff00a2965b8(puVar41);
      FUN_fffffff00a298e80(param_1);
    }
    if ((param_1[0xb] >> 0xf == 0) && ((ulong)(param_1[0xb] >> 6) < param_3 >> 0xe)) {
      puVar41 = (uint *)0x0;
      if (*param_1 != 0) {
        puVar41 = (uint *)((ulong)*param_1 * 0x40 + -0x2400000000);
      }
      if (param_1 == puVar41) goto LAB_fffffff00a25ff94;
      uVar35 = 0;
      uVar40 = 0xfffffffff0000000;
      uVar42 = 1;
      do {
        while( true ) {
          puVar2 = (uint *)0x0;
          if (puVar41[4] != 0) {
            puVar2 = (uint *)((ulong)puVar41[4] * 0x40 + -0x2400000000);
          }
          uVar38 = *(ulong *)(puVar41 + 8);
          if (param_2 <= uVar38 && uVar38 < param_3 + param_2) break;
LAB_fffffff00a260070:
          puVar41 = puVar2;
          if (param_1 == puVar2) {
            uVar42 = uVar35;
            if ((int)uVar35 < 1) goto LAB_fffffff00a25ff94;
            goto LAB_fffffff00a2602a0;
          }
        }
        if ((int)uVar35 < 1) {
          uVar29 = 0;
LAB_fffffff00a260100:
          if (uVar29 != uVar35) goto LAB_fffffff00a260070;
        }
        else {
          uVar29 = 0;
          do {
            if ((uVar38 & uVar40) == local_130[uVar29 * 3]) {
              if (uVar38 < local_130[uVar29 * 3 + 1]) {
                local_130[uVar29 * 3 + 1] = uVar38;
              }
              else {
                uVar30 = uVar38 + 0x3fff;
                if (uVar38 + 0x3fff <= local_130[uVar29 * 3 + 2]) {
                  uVar30 = local_130[uVar29 * 3 + 2];
                }
                local_130[uVar29 * 3 + 2] = uVar30;
              }
              goto LAB_fffffff00a260100;
            }
            uVar29 = uVar29 + 1;
          } while (uVar35 != uVar29);
        }
        if (uVar35 < 8) {
          local_130[uVar35 * 3] = uVar38 & uVar40;
          local_130[uVar35 * 3 + 1] = uVar38;
          local_130[uVar35 * 3 + 2] = uVar38 + 0x3fff;
          uVar35 = uVar35 + 1;
          goto LAB_fffffff00a260070;
        }
        if (uVar35 < 10) {
          lVar26 = 1;
        }
        else {
          uVar40 = 0;
          uVar38 = uVar35 - 1 & 7;
          uVar29 = 8;
          if (uVar38 != 0) {
            uVar29 = uVar38;
          }
          lVar26 = (uVar35 - 1) - uVar29;
          auVar50._8_8_ = local_130[2];
          auVar50._0_8_ = local_130[2];
          auVar55._8_8_ = local_130[2];
          auVar55._0_8_ = local_130[2];
          auVar52._8_8_ = local_130[2];
          auVar52._0_8_ = local_130[2];
          auVar44._8_8_ = local_130[1];
          auVar44._0_8_ = local_130[1];
          auVar54._8_8_ = local_130[2];
          auVar54._0_8_ = local_130[2];
          auVar48._8_8_ = local_130[1];
          auVar48._0_8_ = local_130[1];
          auVar46._8_8_ = local_130[1];
          auVar46._0_8_ = local_130[1];
          auVar45._8_8_ = local_130[1];
          auVar45._0_8_ = local_130[1];
          lVar39 = lVar26;
          do {
            uVar38 = uVar40 | 1;
            uVar29 = uVar40 | 3;
            uVar30 = uVar40 | 5;
            uVar32 = uVar40 | 7;
            auVar5._8_8_ = local_130[uVar38 * 3 + 4];
            auVar5._0_8_ = local_130[uVar38 * 3 + 1];
            auVar17._8_8_ = -(ulong)(local_130[uVar38 * 3 + 4] < auVar44._8_8_);
            auVar17._0_8_ = -(ulong)(local_130[uVar38 * 3 + 1] < auVar44._0_8_);
            auVar44 = auVar44 ^ (auVar44 ^ auVar5) & auVar17;
            auVar11._8_8_ = local_130[uVar29 * 3 + 4];
            auVar11._0_8_ = local_130[uVar29 * 3 + 1];
            auVar18._8_8_ = -(ulong)(local_130[uVar29 * 3 + 4] < auVar48._8_8_);
            auVar18._0_8_ = -(ulong)(local_130[uVar29 * 3 + 1] < auVar48._0_8_);
            auVar48 = auVar48 ^ (auVar48 ^ auVar11) & auVar18;
            auVar13._8_8_ = local_130[uVar30 * 3 + 4];
            auVar13._0_8_ = local_130[uVar30 * 3 + 1];
            auVar19._8_8_ = -(ulong)(local_130[uVar30 * 3 + 4] < auVar46._8_8_);
            auVar19._0_8_ = -(ulong)(local_130[uVar30 * 3 + 1] < auVar46._0_8_);
            auVar46 = auVar46 ^ (auVar46 ^ auVar13) & auVar19;
            auVar15._8_8_ = local_130[uVar32 * 3 + 4];
            auVar15._0_8_ = local_130[uVar32 * 3 + 1];
            auVar20._8_8_ = -(ulong)(local_130[uVar32 * 3 + 4] < auVar45._8_8_);
            auVar20._0_8_ = -(ulong)(local_130[uVar32 * 3 + 1] < auVar45._0_8_);
            auVar45 = auVar45 ^ (auVar45 ^ auVar15) & auVar20;
            auVar10._8_8_ = local_130[uVar38 * 3 + 5];
            auVar10._0_8_ = local_130[uVar38 * 3 + 2];
            auVar21._8_8_ = -(ulong)(auVar50._8_8_ < local_130[uVar38 * 3 + 5]);
            auVar21._0_8_ = -(ulong)(auVar50._0_8_ < local_130[uVar38 * 3 + 2]);
            auVar50 = auVar50 ^ (auVar50 ^ auVar10) & auVar21;
            auVar12._8_8_ = local_130[uVar29 * 3 + 5];
            auVar12._0_8_ = local_130[uVar29 * 3 + 2];
            auVar6._8_8_ = -(ulong)(auVar55._8_8_ < local_130[uVar29 * 3 + 5]);
            auVar6._0_8_ = -(ulong)(auVar55._0_8_ < local_130[uVar29 * 3 + 2]);
            auVar55 = auVar55 ^ (auVar55 ^ auVar12) & auVar6;
            auVar14._8_8_ = local_130[uVar30 * 3 + 5];
            auVar14._0_8_ = local_130[uVar30 * 3 + 2];
            auVar7._8_8_ = -(ulong)(auVar52._8_8_ < local_130[uVar30 * 3 + 5]);
            auVar7._0_8_ = -(ulong)(auVar52._0_8_ < local_130[uVar30 * 3 + 2]);
            auVar52 = auVar52 ^ (auVar52 ^ auVar14) & auVar7;
            auVar16._8_8_ = local_130[uVar32 * 3 + 5];
            auVar16._0_8_ = local_130[uVar32 * 3 + 2];
            auVar8._8_8_ = -(ulong)(auVar54._8_8_ < local_130[uVar32 * 3 + 5]);
            auVar8._0_8_ = -(ulong)(auVar54._0_8_ < local_130[uVar32 * 3 + 2]);
            auVar54 = auVar54 ^ (auVar54 ^ auVar16) & auVar8;
            uVar40 = uVar40 + 8;
            lVar39 = lVar39 + -8;
          } while (lVar39 != 0);
          lVar26 = lVar26 + 1;
          auVar9._8_8_ = -(ulong)(auVar55._8_8_ < auVar50._8_8_);
          auVar9._0_8_ = -(ulong)(auVar55._0_8_ < auVar50._0_8_);
          auVar50 = auVar50 ^ (auVar50 ^ auVar55) & ~auVar9;
          auVar56._0_8_ = -(ulong)(auVar52._0_8_ < auVar50._0_8_);
          auVar56._8_8_ = -(ulong)(auVar52._8_8_ < auVar50._8_8_);
          auVar50 = auVar50 ^ (auVar50 ^ auVar52) & ~auVar56;
          auVar53._0_8_ = -(ulong)(auVar54._0_8_ < auVar50._0_8_);
          auVar53._8_8_ = -(ulong)(auVar54._8_8_ < auVar50._8_8_);
          auVar50 = auVar50 ^ (auVar50 ^ auVar54) & ~auVar53;
          auVar52 = NEON_ext(auVar50,auVar50,8,1);
          local_130[2] = auVar50._0_8_;
          local_130[2] = local_130[2] ^
                         (local_130[2] ^ auVar52._0_8_) & ~-(ulong)(auVar52._0_8_ < local_130[2]);
          auVar51._0_8_ = -(ulong)(auVar44._0_8_ < auVar48._0_8_);
          auVar51._8_8_ = -(ulong)(auVar44._8_8_ < auVar48._8_8_);
          auVar44 = auVar44 ^ (auVar44 ^ auVar48) & ~auVar51;
          auVar49._0_8_ = -(ulong)(auVar44._0_8_ < auVar46._0_8_);
          auVar49._8_8_ = -(ulong)(auVar44._8_8_ < auVar46._8_8_);
          auVar44 = auVar44 ^ (auVar44 ^ auVar46) & ~auVar49;
          auVar47._0_8_ = -(ulong)(auVar44._0_8_ < auVar45._0_8_);
          auVar47._8_8_ = -(ulong)(auVar44._8_8_ < auVar45._8_8_);
          auVar44 = auVar44 ^ (auVar44 ^ auVar45) & ~auVar47;
          auVar45 = NEON_ext(auVar44,auVar44,8,1);
          local_130[1] = auVar44._0_8_;
          local_130[1] = local_130[1] ^
                         (local_130[1] ^ auVar45._0_8_) & ~-(ulong)(local_130[1] < auVar45._0_8_);
        }
        lVar39 = uVar35 - lVar26;
        do {
          uVar35 = local_130[lVar26 * 3 + 1];
          if (local_130[1] <= local_130[lVar26 * 3 + 1]) {
            uVar35 = local_130[1];
          }
          uVar38 = local_130[lVar26 * 3 + 2];
          if (local_130[lVar26 * 3 + 2] <= local_130[2]) {
            uVar38 = local_130[2];
          }
          lVar26 = lVar26 + 1;
          lVar39 = lVar39 + -1;
          local_130[2] = uVar38;
          local_130[1] = uVar35;
        } while (lVar39 != 0);
        uVar40 = 0;
        uVar35 = 1;
        local_130[0] = 0;
      } while (param_1 != puVar41);
    }
    else {
      local_130[1] = param_2;
      local_130[2] = (param_3 + param_2) - 1;
      uVar42 = 1;
    }
LAB_fffffff00a2602a0:
    uVar35 = 0;
    local_1d4 = 0;
    uVar37 = param_7 >> 5 & 1;
    do {
      local_1a4 = DAT_fffffff00acb5750;
      uVar40 = local_130[uVar35 * 3 + 1];
      uVar38 = local_130[uVar35 * 3 + 2];
      local_180 = 0;
      lStack_178 = 0;
      plVar27 = (long *)FUN_fffffff00a1b1358(&DAT_fffffff007c54c80,5);
      if (plVar27 == (long *)0x0) {
        DAT_fffffff00ace86b4 = DAT_fffffff00ace86b4 + 1;
        local_198 = &local_180;
        local_1a4 = 1;
      }
      else {
        if (0x1f < local_1a4) {
          local_1a4 = 0x20;
        }
        lVar26 = tpidr_el1;
        plVar27[0x40] = lVar26;
        local_198 = plVar27;
      }
      if (uVar40 < uVar38) {
        local_1a8 = 0;
        iVar24 = 0;
        uVar36 = 0;
        local_190 = 0;
        bVar22 = false;
        plVar43 = local_198;
        local_1a0 = uVar40;
        do {
          if (param_1[0xb] == 0) break;
          uVar33 = uVar36;
          if ((uVar36 != 0) && ((uVar36 >> 0x14 != 0 || (local_1a0 != uVar40)))) {
            if (iVar24 != 0) {
              FUN_fffffff00a2c38b4(param_1,0,local_198,iVar24);
              plVar43 = local_198;
            }
            lVar26 = *(long *)(param_1 + 0x14);
            if (lVar26 == 0) {
              iVar24 = 0;
              uVar33 = 0;
            }
            else {
              uVar33 = (ushort)param_1[0x1b] + 1;
              *(short *)(param_1 + 0x1b) = (short)uVar33;
              if (uVar33 >> 0x10 != 0) goto LAB_fffffff00a2609bc;
              FUN_fffffff00a1bad04(param_1 + 2);
              (**(code **)(*(long *)(lVar26 + 8) + 0x28))
                        (lVar26,local_190,uVar36,param_4,param_5,0,0,uVar37 | 0x10);
              FUN_fffffff00a298e80(param_1);
              uVar4 = (ushort)param_1[0x1b];
              uVar36 = uVar4 - 1;
              *(short *)(param_1 + 0x1b) = (short)uVar36;
              if (0xffff < uVar36) goto LAB_fffffff00a260a0c;
              uVar36 = uVar36 & 0xffff;
              uVar34 = param_1[0x1d];
              if (((uVar34 >> 0xc & 1) == 0) &&
                 (((*(byte *)((long)param_1 + 0xa9) & uVar4 == 0x40) != 0 || (uVar4 == 0x10)))) {
                if ((uVar34 >> 6 & 1) != 0) {
                  lVar26 = tpidr_el1;
                  plVar1 = (long *)(DAT_fffffff00acae458 +
                                   (ulong)*(ushort *)(lVar26 + 0x1a8) * 0x4000);
                  lVar26 = *plVar1;
                  *plVar1 = lVar26 + 1;
                  FUN_fffffff00a1da0e8(lVar26,(long)param_1 + 6,0,0);
                  uVar34 = param_1[0x1d];
                  uVar36 = (uint)(ushort)param_1[0x1b];
                }
                uVar34 = uVar34 & 0xffffffbf;
                param_1[0x1d] = uVar34;
              }
              if (uVar36 == 0) {
                if ((uVar34 >> 5 & 1) != 0) {
                  FUN_fffffff00a1da0e8((long)param_1 + 5,0,0);
                  uVar34 = param_1[0x1d];
                }
                uVar34 = uVar34 & 0xffffffdf;
                param_1[0x1d] = uVar34;
                if (param_1[0x1c] == 0) goto LAB_fffffff00a260470;
              }
              iVar24 = 0;
              uVar33 = 0;
            }
          }
          while (uVar36 = uVar33, lVar26 = FUN_fffffff00a2beaa4(param_1,uVar40), lVar26 != 0) {
            *(undefined4 *)(plVar43 + 1) = 0;
            iVar25 = FUN_fffffff00a25f444(lVar26,param_6,param_7 & 1,param_8);
            if ((uVar36 == 0) || (iVar25 == 2)) {
              if (iVar25 != 1) {
                if (iVar25 == 0) {
LAB_fffffff00a260698:
                  if ((int)plVar43[1] == 0) break;
                  bVar3 = *(byte *)(lVar26 + 0x2c);
                }
                else {
                  if (iVar25 == 2) {
                    uVar29 = uVar40;
                    if (uVar36 != 0) {
                      uVar29 = local_190;
                    }
                    uVar36 = uVar36 + 0x4000;
                    local_1a0 = uVar40 + 0x4000;
                    local_190 = uVar29;
                    if ((param_7 & 1) != 0) {
                      bVar3 = *(byte *)(lVar26 + 0x2a) & 0xf;
                      bVar22 = true;
                      if ((bVar3 == 1) || (bVar3 == 0xe)) goto LAB_fffffff00a260698;
                      *(byte *)(lVar26 + 0x2d) = *(byte *)(lVar26 + 0x2d) | 4;
                    }
                    bVar22 = true;
                    goto LAB_fffffff00a260698;
                  }
                  local_1a8 = local_1a8 + (*(byte *)(lVar26 + 0x2d) & 1);
                  *(uint *)(plVar43 + 1) = *(uint *)(plVar43 + 1) | 4;
                  bVar3 = *(byte *)(lVar26 + 0x2c);
                }
                if ((bVar3 >> 2 & 1) == 0) {
                  *(byte *)(lVar26 + 0x2c) = bVar3 | 4;
                  if ((*(uint *)(plVar43 + 1) >> 2 & 1) == 0) {
                    *(uint *)(plVar43 + 1) = *(uint *)(plVar43 + 1) | 0x300;
                  }
                }
                *plVar43 = lVar26;
                iVar24 = iVar24 + 1;
                plVar43 = plVar43 + 2;
                if ((int)local_1a4 <= iVar24) {
                  FUN_fffffff00a2c38b4(param_1,0,local_198,iVar24);
                  iVar24 = 0;
                  plVar43 = local_198;
                }
                break;
              }
              FUN_fffffff00a2986d4(param_1,lVar26,0,4);
              uVar33 = uVar36;
            }
            else {
              if (iVar24 != 0) {
                FUN_fffffff00a2c38b4(param_1,0,local_198,iVar24);
                plVar43 = local_198;
              }
              iVar24 = 0;
              lVar26 = *(long *)(param_1 + 0x14);
              uVar33 = 0;
              if (lVar26 != 0) {
                uVar33 = (ushort)param_1[0x1b] + 1;
                *(short *)(param_1 + 0x1b) = (short)uVar33;
                if (uVar33 >> 0x10 != 0) goto LAB_fffffff00a2609bc;
                FUN_fffffff00a1bad04(param_1 + 2);
                (**(code **)(*(long *)(lVar26 + 8) + 0x28))
                          (lVar26,local_190,uVar36,param_4,param_5,0,0,uVar37 | 0x10);
                FUN_fffffff00a298e80(param_1);
                uVar4 = (ushort)param_1[0x1b];
                uVar36 = uVar4 - 1;
                *(short *)(param_1 + 0x1b) = (short)uVar36;
                if (0xffff < uVar36) goto LAB_fffffff00a260a0c;
                uVar36 = uVar36 & 0xffff;
                uVar34 = param_1[0x1d];
                if (((uVar34 >> 0xc & 1) == 0) &&
                   (((*(byte *)((long)param_1 + 0xa9) & uVar4 == 0x40) != 0 || (uVar4 == 0x10)))) {
                  if ((uVar34 >> 6 & 1) != 0) {
                    lVar26 = tpidr_el1;
                    plVar1 = (long *)(DAT_fffffff00acae458 +
                                     (ulong)*(ushort *)(lVar26 + 0x1a8) * 0x4000);
                    lVar26 = *plVar1;
                    *plVar1 = lVar26 + 1;
                    FUN_fffffff00a1da0e8(lVar26,(long)param_1 + 6,0,0);
                    uVar34 = param_1[0x1d];
                    uVar36 = (uint)(ushort)param_1[0x1b];
                  }
                  uVar34 = uVar34 & 0xffffffbf;
                  param_1[0x1d] = uVar34;
                }
                iVar24 = 0;
                uVar33 = 0;
                if (uVar36 == 0) {
                  if ((uVar34 >> 5 & 1) != 0) {
                    FUN_fffffff00a1da0e8((long)param_1 + 5,0,0);
                    uVar34 = param_1[0x1d];
                  }
                  iVar24 = 0;
                  uVar34 = uVar34 & 0xffffffdf;
                  param_1[0x1d] = uVar34;
                  uVar33 = 0;
                  if (param_1[0x1c] == 0) {
LAB_fffffff00a260470:
                    if ((uVar34 >> 2 & 1) != 0) {
                      FUN_fffffff00a1da0e8((long)param_1 + 2,0,0);
                      uVar34 = param_1[0x1d];
                    }
                    iVar24 = 0;
                    param_1[0x1d] = uVar34 & 0xfffffffb;
                    uVar33 = 0;
                  }
                }
              }
            }
          }
          uVar40 = uVar40 + 0x4000;
        } while (uVar40 < uVar38);
        local_1a8 = local_1a8 << 0xe;
        if (bVar22) {
          local_1d4 = 1;
        }
        lVar26 = *(long *)(param_1 + 0x14);
      }
      else {
        local_190 = 0;
        uVar36 = 0;
        iVar24 = 0;
        local_1a8 = 0;
        lVar26 = *(long *)(param_1 + 0x14);
      }
      if (lVar26 != 0) {
        uVar28 = tpidr_el1;
        uVar28 = FUN_fffffff00a22d63c(uVar28);
        if (*(undefined **)(lVar26 + 8) == &DAT_fffffff007bb1f10) {
          uVar31 = *(undefined8 *)(lVar26 + 0x20);
        }
        else {
          uVar31 = 0;
        }
        FUN_fffffff00a1faa7c(uVar28,local_1a8,4,uVar31);
      }
      if (iVar24 != 0) {
        FUN_fffffff00a2c38b4(param_1,0,local_198,iVar24);
      }
      if ((uVar36 != 0) && (lVar26 = *(long *)(param_1 + 0x14), lVar26 != 0)) {
        uVar33 = (ushort)param_1[0x1b] + 1;
        *(short *)(param_1 + 0x1b) = (short)uVar33;
        if (uVar33 >> 0x10 != 0) goto LAB_fffffff00a2609bc;
        FUN_fffffff00a1bad04(param_1 + 2);
        (**(code **)(*(long *)(lVar26 + 8) + 0x28))
                  (lVar26,local_190,uVar36,param_4,param_5,0,0,uVar37 | 0x10);
        FUN_fffffff00a298e80(param_1);
        uVar4 = (ushort)param_1[0x1b];
        uVar36 = uVar4 - 1;
        *(short *)(param_1 + 0x1b) = (short)uVar36;
        if (0xffff < uVar36) goto LAB_fffffff00a260a0c;
        uVar36 = uVar36 & 0xffff;
        uVar33 = param_1[0x1d];
        if (((uVar33 >> 0xc & 1) == 0) &&
           (((*(byte *)((long)param_1 + 0xa9) & uVar4 == 0x40) != 0 || (uVar4 == 0x10)))) {
          if ((uVar33 >> 6 & 1) != 0) {
            lVar26 = tpidr_el1;
            plVar43 = (long *)(DAT_fffffff00acae458 + (ulong)*(ushort *)(lVar26 + 0x1a8) * 0x4000);
            lVar26 = *plVar43;
            *plVar43 = lVar26 + 1;
            FUN_fffffff00a1da0e8(lVar26,(long)param_1 + 6,0,0);
            uVar33 = param_1[0x1d];
            uVar36 = (uint)(ushort)param_1[0x1b];
          }
          uVar33 = uVar33 & 0xffffffbf;
          param_1[0x1d] = uVar33;
        }
        if (uVar36 == 0) {
          if ((uVar33 >> 5 & 1) != 0) {
            FUN_fffffff00a1da0e8((long)param_1 + 5,0,0);
            uVar33 = param_1[0x1d];
          }
          uVar36 = uVar33 & 0xffffffdf;
          param_1[0x1d] = uVar36;
          if (param_1[0x1c] == 0) {
            if ((uVar33 >> 2 & 1) != 0) {
              FUN_fffffff00a1da0e8((long)param_1 + 2,0,0);
              uVar36 = param_1[0x1d];
            }
            param_1[0x1d] = uVar36 & 0xfffffffb;
          }
        }
      }
      if (plVar27 != (long *)0x0) {
        plVar27[0x40] = 0;
        FUN_fffffff00a228f2c(&DAT_fffffff007c54c80);
      }
      uVar35 = uVar35 + 1;
    } while (uVar35 != uVar42);
  }
  else {
    if (puVar41 != (uint *)0x0 && puVar41 != param_1) {
      FUN_fffffff00a1bad04(puVar41 + 2);
      FUN_fffffff00a2965b8(puVar41);
      FUN_fffffff00a298e80(param_1);
    }
LAB_fffffff00a25ff94:
    local_1d4 = 0;
  }
  if (DAT_fffffff00acd0000 != local_130[0x18]) {
                    /* WARNING: Subroutine does not return */
    FUN_fffffff00a9eb0c4();
  }
  return local_1d4;
LAB_fffffff00a25fd54:
  if (iVar24 == 5) {
    local_134 = 3;
    FUN_fffffff00a298e80(puVar41);
    uVar37 = (ushort)puVar41[0x1b] + 1;
    *(short *)(puVar41 + 0x1b) = (short)uVar37;
    if (uVar37 >> 0x10 != 0) goto LAB_fffffff00a2609bc;
  }
  else {
    if (iVar24 != 6) {
LAB_fffffff00a2609c8:
                    /* WARNING: Subroutine does not return */
      FUN_fffffff00a9ebcbc("vm_object_update: unexpected error 0x%x from vm_fault_page()\n @%s:%d");
    }
    local_134 = 3;
  }
LAB_fffffff00a25fc80:
  uVar42 = uVar42 + 0x4000;
  if (uVar35 <= uVar42) goto LAB_fffffff00a25fe7c;
  goto LAB_fffffff00a25fc8c;
LAB_fffffff00a25fe7c:
  uVar37 = (uint)(ushort)puVar41[0x1b];
LAB_fffffff00a25fe88:
  uVar36 = (uVar37 & 0xffff) - 1;
  *(short *)(puVar41 + 0x1b) = (short)uVar36;
  if (0xffff < uVar36) {
LAB_fffffff00a260a0c:
                    /* WARNING: Subroutine does not return */
    FUN_fffffff00a9ebcbc("vm_object_paging_end(%p): underflow\n @%s:%d");
  }
  uVar36 = uVar36 & 0xffff;
  uVar33 = puVar41[0x1d];
  if (((uVar33 >> 0xc & 1) == 0) &&
     (((*(byte *)((long)puVar41 + 0xa9) & (uVar37 & 0xffff) == 0x40) != 0 ||
      ((uVar37 & 0xffff) == 0x10)))) {
    if ((uVar33 >> 6 & 1) != 0) {
      lVar26 = tpidr_el1;
      plVar27 = (long *)(DAT_fffffff00acae458 + (ulong)*(ushort *)(lVar26 + 0x1a8) * 0x4000);
      lVar26 = *plVar27;
      *plVar27 = lVar26 + 1;
      FUN_fffffff00a1da0e8(lVar26,(long)puVar41 + 6,0,0);
      uVar33 = puVar41[0x1d];
      uVar36 = (uint)(ushort)puVar41[0x1b];
    }
    uVar33 = uVar33 & 0xffffffbf;
    puVar41[0x1d] = uVar33;
  }
  if (uVar36 == 0) {
    if ((uVar33 >> 5 & 1) != 0) {
      FUN_fffffff00a1da0e8((long)puVar41 + 5,0,0);
      uVar33 = puVar41[0x1d];
    }
    uVar37 = uVar33 & 0xffffffdf;
    puVar41[0x1d] = uVar37;
    if (puVar41[0x1c] == 0) {
      if ((uVar33 >> 2 & 1) != 0) {
        FUN_fffffff00a1da0e8((long)puVar41 + 2,0,0);
        uVar37 = puVar41[0x1d];
      }
      puVar41[0x1d] = uVar37 & 0xfffffffb;
    }
  }
  goto LAB_fffffff00a25ff64;
}

