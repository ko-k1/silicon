
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_fffffff00a29be58
               (uint *param_1,ulong param_2,ulong param_3,undefined8 param_4,undefined8 param_5,
               undefined8 param_6,uint param_7,undefined8 param_8)

{
  long *plVar1;
  byte bVar2;
  uint *puVar3;
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
  byte bVar22;
  byte bVar23;
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
  undefined4 uVar34;
  uint uVar35;
  ulong uVar36;
  uint uVar37;
  uint uVar38;
  ulong uVar39;
  long lVar40;
  ulong uVar41;
  uint *puVar42;
  ulong uVar43;
  long *plVar44;
  undefined4 in_wzr;
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
  undefined1 auVar57 [16];
  ulong in_stack_fffffffffffffdf0;
  uint local_1ac;
  ulong local_1a8;
  int local_19c;
  ulong local_198;
  long *local_190;
  long local_180;
  long lStack_178;
  undefined8 local_170;
  ulong uStack_168;
  ulong uStack_160;
  undefined8 local_158;
  undefined8 local_148;
  long local_140;
  long local_138;
  ulong local_130 [26];
  
  local_130[0x18] = DAT_fffffff00ad10000;
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
  uVar35 = param_7 >> 3 & 1;
  if ((param_7 & 3) == 1) {
    uVar35 = 1;
  }
  local_130[1] = 0;
  local_130[0] = 0;
  local_130[3] = 0;
  local_130[2] = 0;
  if (uVar35 == 1) {
    lVar26 = (ulong)param_1[0x3a] + 1;
    param_1[0x3a] = (uint)lVar26;
    if (lVar26 != lVar26 * 0x80000000 >> 0x1f) {
                    /* WARNING: Subroutine does not return */
      FUN_fffffff00aa2c834("vm_object_pl_req_begin(%p): overflow\n @%s:%d");
    }
LAB_fffffff00a29bf24:
    puVar42 = *(uint **)(param_1 + 0xe);
    if (puVar42 != (uint *)0x0) {
      uVar38 = 1;
      do {
        iVar24 = FUN_fffffff00a2daeac(puVar42);
        FUN_fffffff00a1f6fdc(param_1 + 2);
        if (iVar24 != 0) {
          if (puVar42[10] + 0xf0000001 < 0xf0000002) {
                    /* WARNING: Subroutine does not return */
            FUN_fffffff00aa41564(puVar42 + 10);
          }
          puVar42[10] = puVar42[10] + 1;
          break;
        }
        uVar37 = uVar38;
        if (0x1e < uVar38) {
          uVar37 = 0x1f;
        }
        (&DAT_fffffff00ad13da0)[uVar37] = (&DAT_fffffff00ad13da0)[uVar37] + 1;
        uVar37 = uVar38;
        if (6 < uVar38) {
          uVar37 = 7;
        }
        FUN_fffffff00a2132b8(FUN_fffffff00a1f3264,0,(&DAT_fffffff00acec410)[uVar37],1000);
        FUN_fffffff00a213eb8(0,0,0);
        FUN_fffffff00a2d57b8(param_1);
        puVar42 = *(uint **)(param_1 + 0xe);
        uVar38 = uVar38 + 1;
      } while (puVar42 != (uint *)0x0);
    }
  }
  else {
    if ((param_7 >> 4 & 1) != 0) goto LAB_fffffff00a29bf24;
    puVar42 = (uint *)0x0;
  }
  uVar38 = 0;
  if (puVar42 != (uint *)0x0) {
    uVar38 = uVar35;
  }
  if (((param_7 >> 4 & 1) != 0) || (uVar38 != 0)) {
    local_148 = 0;
    local_140 = 0;
    local_138 = 0;
    lStack_178 = 0;
    local_180 = 0;
    if (puVar42 == (uint *)0x0) {
      uVar36 = param_3 + param_2;
      uVar43 = param_2;
      puVar42 = param_1;
    }
    else {
      uVar36 = *(ulong *)(puVar42 + 0x16);
      uVar41 = 0;
      if (uVar36 - param_2 <= param_3) {
        uVar41 = param_3 - (uVar36 - param_2);
      }
      if (uVar36 <= param_2) {
        uVar41 = param_3;
      }
      uVar39 = *(ulong *)(puVar42 + 6);
      uVar43 = 0;
      if (uVar36 <= param_2) {
        uVar43 = param_2 - uVar36;
      }
      if (uVar39 <= uVar43) {
        uVar43 = uVar39;
      }
      uVar36 = uVar39 - uVar43;
      if (uVar41 + uVar43 <= uVar39) {
        uVar36 = uVar41;
      }
      uVar36 = uVar36 + uVar43;
    }
    local_170 = 2;
    uStack_168 = uVar43;
    uStack_160 = uVar36;
    local_158 = 2;
    uVar38 = (ushort)puVar42[0x1b] + 1;
    *(short *)(puVar42 + 0x1b) = (short)uVar38;
    if (uVar38 >> 0x10 != 0) {
LAB_fffffff00a29cfac:
                    /* WARNING: Subroutine does not return */
      FUN_fffffff00aa2c834("vm_object_paging_begin(%p): overflow\n @%s:%d");
    }
    if (uVar43 < uVar36) {
LAB_fffffff00a29c0dc:
      do {
        local_148 = CONCAT44(3,(undefined4)local_148);
        local_138 = 0;
        in_stack_fffffffffffffdf0 = in_stack_fffffffffffffdf0 & 0xffffffff00000000;
        lStack_178 = uVar36 - uVar43;
        lVar26 = FUN_fffffff00a2a3db4
                           (puVar42,uVar43,3,0,0,(long)&local_148 + 4,&local_138,&local_140,0,
                            &local_148,in_stack_fffffffffffffdf0,&local_180,0);
        iVar24 = (int)lVar26;
        if (iVar24 < 3) {
          if (iVar24 == 1) {
            local_148 = CONCAT44(3,(undefined4)local_148);
            FUN_fffffff00a2d57b8(puVar42);
            uVar38 = (ushort)puVar42[0x1b] + 1;
            *(short *)(puVar42 + 0x1b) = (short)uVar38;
          }
          else {
            if (iVar24 != 2) {
              if (iVar24 != 0) goto LAB_fffffff00a29cfb8;
              if (local_140 != 0) {
                lVar26 = 0;
                if (*(uint *)(local_138 + 0x1c) != 0) {
                  lVar26 = (ulong)*(uint *)(local_138 + 0x1c) * 0x40 + -0x2400000000;
                }
                FUN_fffffff00a2a6020(lVar26);
                lVar26 = FUN_fffffff00a2d57b8(puVar42);
                uVar38 = (ushort)puVar42[0x1b] + 1;
                *(short *)(puVar42 + 0x1b) = (short)uVar38;
                if (uVar38 >> 0x10 != 0) goto LAB_fffffff00a29cfac;
              }
              if ((1L << (*(byte *)(local_138 + 0x2a) & 0xf) & 0x3c60U) == 0) {
                lVar40 = tpidr_el1;
                *(int *)(lVar40 + 0x1b8) = *(int *)(lVar40 + 0x1b8) + 1;
                if (_DAT_fffffff00ad4d188 == 0) {
                  _DAT_fffffff00ad4d188 = (ulong)*(uint *)(lVar40 + 0x4e0) | 0x30000000;
                }
                else {
                  FUN_fffffff00a1f2328(&DAT_fffffff00ad4d180,lVar40,1);
                }
                lVar26 = local_138;
                if ((1L << (*(byte *)(local_138 + 0x2a) & 0xf) & 0x3c60U) == 0) {
                  lVar26 = FUN_fffffff00a2f9a5c(local_138,1);
                }
                if (DAT_fffffff00ad4d188 == *(int *)(lVar40 + 0x4e0)) {
                  _DAT_fffffff00ad4d188 = CONCAT44(DAT_fffffff00ad4d188_4,in_wzr);
                }
                else {
                  lVar26 = FUN_fffffff00a1f2e68(&DAT_fffffff00ad4d180,lVar40);
                }
              }
              FUN_fffffff00a2d9f44(lVar26,local_138);
              goto LAB_fffffff00a29c0d0;
            }
            local_148 = CONCAT44(3,(undefined4)local_148);
            FUN_fffffff00a2d57b8(puVar42);
            uVar38 = (ushort)puVar42[0x1b] + 1;
            *(short *)(puVar42 + 0x1b) = (short)uVar38;
          }
        }
        else {
          if (iVar24 != 3) goto LAB_fffffff00a29c1a4;
          FUN_fffffff00a2fd0b4(0);
          local_148 = CONCAT44(3,(undefined4)local_148);
          FUN_fffffff00a2d57b8(puVar42);
          uVar38 = (ushort)puVar42[0x1b] + 1;
          *(short *)(puVar42 + 0x1b) = (short)uVar38;
        }
        if (uVar38 >> 0x10 != 0) goto LAB_fffffff00a29cfac;
      } while( true );
    }
    goto LAB_fffffff00a29c2dc;
  }
LAB_fffffff00a29c3b8:
  if ((param_7 & 0x18) == 0) {
    if (puVar42 != (uint *)0x0 && puVar42 != param_1) {
      FUN_fffffff00a1f6fdc(puVar42 + 2);
      FUN_fffffff00a2d2ef0(puVar42);
      FUN_fffffff00a2d57b8(param_1);
    }
    if ((param_1[0xb] >> 0xf != 0) || (param_3 >> 0xe <= (ulong)(param_1[0xb] >> 6))) {
      local_130[1] = param_2;
      local_130[2] = (param_3 + param_2) - 1;
      uVar43 = 1;
LAB_fffffff00a29c6dc:
      uVar36 = 0;
      bVar23 = 0;
      uVar34 = 0x10;
      if ((param_7 & 0x20) != 0) {
        uVar34 = 0x11;
      }
LAB_fffffff00a29c710:
      local_1ac = DAT_fffffff00acf5750;
      uVar41 = local_130[uVar36 * 3 + 1];
      uVar39 = local_130[uVar36 * 3 + 2];
      local_180 = 0;
      lStack_178 = 0;
      local_140 = 0;
      plVar27 = (long *)FUN_fffffff00a1ed630(&DAT_fffffff007c61de0,5);
      if (plVar27 == (long *)0x0) {
        DAT_fffffff00ad2878c = DAT_fffffff00ad2878c + 1;
        local_190 = &local_180;
        local_1ac = 1;
      }
      else {
        if (0x1f < local_1ac) {
          local_1ac = 0x20;
        }
        lVar26 = tpidr_el1;
        plVar27[0x40] = lVar26;
        local_190 = plVar27;
      }
      if (uVar41 < uVar39) {
        local_19c = 0;
        iVar24 = 0;
        uVar38 = 0;
        local_198 = 0;
        bVar22 = 0;
        plVar44 = local_190;
        local_1a8 = uVar41;
LAB_fffffff00a29c7d0:
        lVar26 = local_140;
        if (param_1[0xb] != 0) {
          uVar37 = uVar38;
          if ((uVar38 != 0) && ((uVar38 >> 0x14 != 0 || (local_1a8 != uVar41)))) {
            if (local_140 != 0) {
              local_140 = 0;
              FUN_fffffff00a1f6fdc(lVar26 + 8);
            }
            if (iVar24 != 0) {
              FUN_fffffff00a300478(param_1,0,local_190,iVar24);
              plVar44 = local_190;
            }
            lVar26 = *(long *)(param_1 + 0x14);
            if (lVar26 == 0) {
              iVar24 = 0;
              uVar37 = 0;
            }
            else {
              uVar37 = (ushort)param_1[0x1b] + 1;
              *(short *)(param_1 + 0x1b) = (short)uVar37;
              if (uVar37 >> 0x10 != 0) goto LAB_fffffff00a29cfac;
              FUN_fffffff00a1f6fdc(param_1 + 2);
              (**(code **)(*(long *)(lVar26 + 8) + 0x28))
                        (lVar26,local_198,uVar38,param_4,param_5,0,0,uVar34);
              FUN_fffffff00a2d57b8(param_1);
              uVar4 = (ushort)param_1[0x1b];
              uVar38 = uVar4 - 1;
              *(short *)(param_1 + 0x1b) = (short)uVar38;
              if (0xffff < uVar38) goto LAB_fffffff00a29cffc;
              uVar38 = uVar38 & 0xffff;
              uVar33 = param_1[0x1d];
              if (((uVar33 >> 0xc & 1) == 0) &&
                 (((*(byte *)((long)param_1 + 0xa9) & uVar4 == 0x40) != 0 || (uVar4 == 0x10)))) {
                if ((uVar33 >> 6 & 1) != 0) {
                  lVar26 = tpidr_el1;
                  plVar1 = (long *)(DAT_fffffff00acee458 +
                                   (ulong)*(ushort *)(lVar26 + 0x1a8) * 0x4000);
                  lVar26 = *plVar1;
                  *plVar1 = lVar26 + 1;
                  FUN_fffffff00a216478(lVar26,(long)param_1 + 6,0,0);
                  uVar33 = param_1[0x1d];
                  uVar38 = (uint)(ushort)param_1[0x1b];
                }
                uVar33 = uVar33 & 0xffffffbf;
                param_1[0x1d] = uVar33;
              }
              if (uVar38 == 0) {
                if ((uVar33 >> 5 & 1) != 0) {
                  FUN_fffffff00a216478((long)param_1 + 5,0,0);
                  uVar33 = param_1[0x1d];
                }
                uVar33 = uVar33 & 0xffffffdf;
                param_1[0x1d] = uVar33;
                if (param_1[0x1c] == 0) goto LAB_fffffff00a29c8ec;
              }
              iVar24 = 0;
              uVar37 = 0;
            }
          }
LAB_fffffff00a29c95c:
          do {
            uVar38 = uVar37;
            lVar26 = FUN_fffffff00a2fb660(param_1,uVar41);
            if (lVar26 == 0) goto LAB_fffffff00a29c7bc;
            *(undefined4 *)(plVar44 + 1) = 0;
            iVar25 = FUN_fffffff00a29b858(lVar26,param_6,param_7 & 1,param_8);
            lVar40 = local_140;
            if ((uVar38 != 0) && (iVar25 != 2)) {
              if (local_140 != 0) {
                local_140 = 0;
                FUN_fffffff00a1f6fdc(lVar40 + 8);
              }
              if (iVar24 != 0) {
                FUN_fffffff00a300478(param_1,0,local_190,iVar24);
                plVar44 = local_190;
              }
              iVar24 = 0;
              lVar26 = *(long *)(param_1 + 0x14);
              uVar37 = 0;
              if (lVar26 != 0) {
                uVar37 = (ushort)param_1[0x1b] + 1;
                *(short *)(param_1 + 0x1b) = (short)uVar37;
                if (uVar37 >> 0x10 != 0) goto LAB_fffffff00a29cfac;
                FUN_fffffff00a1f6fdc(param_1 + 2);
                (**(code **)(*(long *)(lVar26 + 8) + 0x28))
                          (lVar26,local_198,uVar38,param_4,param_5,0,0,uVar34);
                FUN_fffffff00a2d57b8(param_1);
                uVar4 = (ushort)param_1[0x1b];
                uVar38 = uVar4 - 1;
                *(short *)(param_1 + 0x1b) = (short)uVar38;
                if (0xffff < uVar38) goto LAB_fffffff00a29cffc;
                uVar38 = uVar38 & 0xffff;
                uVar33 = param_1[0x1d];
                if (((uVar33 >> 0xc & 1) == 0) &&
                   (((*(byte *)((long)param_1 + 0xa9) & uVar4 == 0x40) != 0 || (uVar4 == 0x10)))) {
                  if ((uVar33 >> 6 & 1) != 0) {
                    lVar26 = tpidr_el1;
                    plVar1 = (long *)(DAT_fffffff00acee458 +
                                     (ulong)*(ushort *)(lVar26 + 0x1a8) * 0x4000);
                    lVar26 = *plVar1;
                    *plVar1 = lVar26 + 1;
                    FUN_fffffff00a216478(lVar26,(long)param_1 + 6,0,0);
                    uVar33 = param_1[0x1d];
                    uVar38 = (uint)(ushort)param_1[0x1b];
                  }
                  uVar33 = uVar33 & 0xffffffbf;
                  param_1[0x1d] = uVar33;
                }
                iVar24 = 0;
                uVar37 = 0;
                if (uVar38 == 0) {
                  if ((uVar33 >> 5 & 1) != 0) {
                    FUN_fffffff00a216478((long)param_1 + 5,0,0);
                    uVar33 = param_1[0x1d];
                  }
                  iVar24 = 0;
                  uVar33 = uVar33 & 0xffffffdf;
                  param_1[0x1d] = uVar33;
                  uVar37 = 0;
                  if (param_1[0x1c] == 0) {
LAB_fffffff00a29c8ec:
                    if ((uVar33 >> 2 & 1) != 0) {
                      FUN_fffffff00a216478((long)param_1 + 2,0,0);
                      uVar33 = param_1[0x1d];
                    }
                    iVar24 = 0;
                    param_1[0x1d] = uVar33 & 0xfffffffb;
                    uVar37 = 0;
                  }
                }
              }
              goto LAB_fffffff00a29c95c;
            }
            uVar37 = uVar38;
            if (1 < iVar25) {
              if (iVar25 == 3) {
                if ((*(byte *)(lVar26 + 0x2d) & 1) != 0) {
                  *(byte *)(lVar26 + 0x2c) = *(byte *)(lVar26 + 0x2c) | 4;
                  iVar25 = FUN_fffffff00a2a6c3c(param_1,&local_140);
                  if (iVar25 != 0) {
                    local_138 = 0;
                    uVar28 = FUN_fffffff00a2a6d34(lVar26,param_1[0x2a] >> 1 & 0x10000,&local_138);
                    if ((int)uVar28 == 1) {
                      FUN_fffffff00a2d9f44(uVar28,lVar26);
                      lVar26 = local_140;
                      uVar28 = FUN_fffffff00a2fb660(local_140,local_138);
                      FUN_fffffff00a1f6fdc(param_1 + 2);
                      FUN_fffffff00a2d500c(lVar26,uVar28,0,1);
                      local_140 = 0;
                    }
                    else {
                      if ((int)uVar28 != 2) goto LAB_fffffff00a29cba8;
                      FUN_fffffff00a2d9f44(uVar28,lVar26);
                      lVar26 = local_140;
                      if (local_140 != 0) {
                        local_140 = 0;
                        FUN_fffffff00a1f6fdc(lVar26 + 8);
                      }
                      FUN_fffffff00a1f6fdc(param_1 + 2);
                      FUN_fffffff00a2fd0b4(0);
                    }
                    FUN_fffffff00a2d57b8(param_1);
                    goto LAB_fffffff00a29c95c;
                  }
                }
LAB_fffffff00a29cba8:
                local_19c = local_19c + (*(byte *)(lVar26 + 0x2d) & 1);
                *(uint *)(plVar44 + 1) = *(uint *)(plVar44 + 1) | 4;
              }
              else {
                uVar29 = uVar41;
                if (uVar38 != 0) {
                  uVar29 = local_198;
                }
                uVar38 = uVar38 + 0x4000;
                local_1a8 = uVar41 + 0x4000;
                local_198 = uVar29;
                if ((param_7 & 1) != 0) {
                  bVar2 = *(byte *)(lVar26 + 0x2a) & 0xf;
                  bVar22 = 1;
                  if ((bVar2 == 1) || (bVar2 == 0xe)) goto LAB_fffffff00a29cc20;
                  *(byte *)(lVar26 + 0x2d) = *(byte *)(lVar26 + 0x2d) | 4;
                }
                bVar22 = 1;
LAB_fffffff00a29cc20:
                if ((int)plVar44[1] == 0) goto LAB_fffffff00a29c7bc;
              }
              lVar40 = local_140;
              if ((*(byte *)(lVar26 + 0x2c) >> 2 & 1) == 0) {
                *(byte *)(lVar26 + 0x2c) = *(byte *)(lVar26 + 0x2c) | 4;
                if ((*(uint *)(plVar44 + 1) >> 2 & 1) == 0) {
                  *(uint *)(plVar44 + 1) = *(uint *)(plVar44 + 1) | 0x300;
                }
              }
              *plVar44 = lVar26;
              iVar24 = iVar24 + 1;
              plVar44 = plVar44 + 2;
              if ((int)local_1ac <= iVar24) {
                if (local_140 != 0) {
                  local_140 = 0;
                  FUN_fffffff00a1f6fdc(lVar40 + 8);
                }
                FUN_fffffff00a300478(param_1,0,local_190,iVar24);
                iVar24 = 0;
                plVar44 = local_190;
              }
              goto LAB_fffffff00a29c7bc;
            }
            if (iVar25 != 1) goto LAB_fffffff00a29cc20;
            if (local_140 != 0) {
              local_140 = 0;
              FUN_fffffff00a1f6fdc(lVar40 + 8);
            }
            FUN_fffffff00a2d500c(param_1,lVar26,0,4);
          } while( true );
        }
        goto LAB_fffffff00a29ccec;
      }
      local_19c = 0;
      iVar24 = 0;
      uVar38 = 0;
      local_198 = 0;
      lVar26 = *(long *)(param_1 + 0x14);
      goto joined_r0xfffffff00a29cd24;
    }
    puVar42 = (uint *)0x0;
    if (*param_1 != 0) {
      puVar42 = (uint *)((ulong)*param_1 * 0x40 + -0x2400000000);
    }
    if (param_1 != puVar42) {
      uVar36 = 0;
      uVar41 = 0xfffffffff0000000;
      uVar43 = 1;
      do {
        while( true ) {
          puVar3 = (uint *)0x0;
          if (puVar42[4] != 0) {
            puVar3 = (uint *)((ulong)puVar42[4] * 0x40 + -0x2400000000);
          }
          uVar39 = *(ulong *)(puVar42 + 8);
          if (param_2 <= uVar39 && uVar39 < param_3 + param_2) break;
LAB_fffffff00a29c4a4:
          puVar42 = puVar3;
          if (param_1 == puVar3) {
            uVar43 = uVar36;
            if ((int)uVar36 < 1) goto LAB_fffffff00a29cf7c;
            goto LAB_fffffff00a29c6dc;
          }
        }
        if ((int)uVar36 < 1) {
          uVar29 = 0;
LAB_fffffff00a29c534:
          if (uVar29 != uVar36) goto LAB_fffffff00a29c4a4;
        }
        else {
          uVar29 = 0;
          do {
            if ((uVar39 & uVar41) == local_130[uVar29 * 3]) {
              if (uVar39 < local_130[uVar29 * 3 + 1]) {
                local_130[uVar29 * 3 + 1] = uVar39;
              }
              else {
                uVar30 = uVar39 + 0x3fff;
                if (uVar39 + 0x3fff <= local_130[uVar29 * 3 + 2]) {
                  uVar30 = local_130[uVar29 * 3 + 2];
                }
                local_130[uVar29 * 3 + 2] = uVar30;
              }
              goto LAB_fffffff00a29c534;
            }
            uVar29 = uVar29 + 1;
          } while (uVar36 != uVar29);
        }
        if (uVar36 < 8) {
          local_130[uVar36 * 3] = uVar39 & uVar41;
          local_130[uVar36 * 3 + 1] = uVar39;
          local_130[uVar36 * 3 + 2] = uVar39 + 0x3fff;
          uVar36 = uVar36 + 1;
          goto LAB_fffffff00a29c4a4;
        }
        if (uVar36 < 10) {
          lVar26 = 1;
        }
        else {
          uVar41 = 0;
          uVar39 = uVar36 - 1 & 7;
          uVar29 = 8;
          if (uVar39 != 0) {
            uVar29 = uVar39;
          }
          lVar26 = (uVar36 - 1) - uVar29;
          auVar51._8_8_ = local_130[2];
          auVar51._0_8_ = local_130[2];
          auVar56._8_8_ = local_130[2];
          auVar56._0_8_ = local_130[2];
          auVar53._8_8_ = local_130[2];
          auVar53._0_8_ = local_130[2];
          auVar45._8_8_ = local_130[1];
          auVar45._0_8_ = local_130[1];
          auVar55._8_8_ = local_130[2];
          auVar55._0_8_ = local_130[2];
          auVar49._8_8_ = local_130[1];
          auVar49._0_8_ = local_130[1];
          auVar47._8_8_ = local_130[1];
          auVar47._0_8_ = local_130[1];
          auVar46._8_8_ = local_130[1];
          auVar46._0_8_ = local_130[1];
          lVar40 = lVar26;
          do {
            uVar39 = uVar41 | 1;
            uVar29 = uVar41 | 3;
            uVar30 = uVar41 | 5;
            uVar32 = uVar41 | 7;
            auVar5._8_8_ = local_130[uVar39 * 3 + 4];
            auVar5._0_8_ = local_130[uVar39 * 3 + 1];
            auVar17._8_8_ = -(ulong)(local_130[uVar39 * 3 + 4] < auVar45._8_8_);
            auVar17._0_8_ = -(ulong)(local_130[uVar39 * 3 + 1] < auVar45._0_8_);
            auVar45 = auVar45 ^ (auVar45 ^ auVar5) & auVar17;
            auVar11._8_8_ = local_130[uVar29 * 3 + 4];
            auVar11._0_8_ = local_130[uVar29 * 3 + 1];
            auVar18._8_8_ = -(ulong)(local_130[uVar29 * 3 + 4] < auVar49._8_8_);
            auVar18._0_8_ = -(ulong)(local_130[uVar29 * 3 + 1] < auVar49._0_8_);
            auVar49 = auVar49 ^ (auVar49 ^ auVar11) & auVar18;
            auVar13._8_8_ = local_130[uVar30 * 3 + 4];
            auVar13._0_8_ = local_130[uVar30 * 3 + 1];
            auVar19._8_8_ = -(ulong)(local_130[uVar30 * 3 + 4] < auVar47._8_8_);
            auVar19._0_8_ = -(ulong)(local_130[uVar30 * 3 + 1] < auVar47._0_8_);
            auVar47 = auVar47 ^ (auVar47 ^ auVar13) & auVar19;
            auVar15._8_8_ = local_130[uVar32 * 3 + 4];
            auVar15._0_8_ = local_130[uVar32 * 3 + 1];
            auVar20._8_8_ = -(ulong)(local_130[uVar32 * 3 + 4] < auVar46._8_8_);
            auVar20._0_8_ = -(ulong)(local_130[uVar32 * 3 + 1] < auVar46._0_8_);
            auVar46 = auVar46 ^ (auVar46 ^ auVar15) & auVar20;
            auVar10._8_8_ = local_130[uVar39 * 3 + 5];
            auVar10._0_8_ = local_130[uVar39 * 3 + 2];
            auVar21._8_8_ = -(ulong)(auVar51._8_8_ < local_130[uVar39 * 3 + 5]);
            auVar21._0_8_ = -(ulong)(auVar51._0_8_ < local_130[uVar39 * 3 + 2]);
            auVar51 = auVar51 ^ (auVar51 ^ auVar10) & auVar21;
            auVar12._8_8_ = local_130[uVar29 * 3 + 5];
            auVar12._0_8_ = local_130[uVar29 * 3 + 2];
            auVar6._8_8_ = -(ulong)(auVar56._8_8_ < local_130[uVar29 * 3 + 5]);
            auVar6._0_8_ = -(ulong)(auVar56._0_8_ < local_130[uVar29 * 3 + 2]);
            auVar56 = auVar56 ^ (auVar56 ^ auVar12) & auVar6;
            auVar14._8_8_ = local_130[uVar30 * 3 + 5];
            auVar14._0_8_ = local_130[uVar30 * 3 + 2];
            auVar7._8_8_ = -(ulong)(auVar53._8_8_ < local_130[uVar30 * 3 + 5]);
            auVar7._0_8_ = -(ulong)(auVar53._0_8_ < local_130[uVar30 * 3 + 2]);
            auVar53 = auVar53 ^ (auVar53 ^ auVar14) & auVar7;
            auVar16._8_8_ = local_130[uVar32 * 3 + 5];
            auVar16._0_8_ = local_130[uVar32 * 3 + 2];
            auVar8._8_8_ = -(ulong)(auVar55._8_8_ < local_130[uVar32 * 3 + 5]);
            auVar8._0_8_ = -(ulong)(auVar55._0_8_ < local_130[uVar32 * 3 + 2]);
            auVar55 = auVar55 ^ (auVar55 ^ auVar16) & auVar8;
            uVar41 = uVar41 + 8;
            lVar40 = lVar40 + -8;
          } while (lVar40 != 0);
          lVar26 = lVar26 + 1;
          auVar9._8_8_ = -(ulong)(auVar56._8_8_ < auVar51._8_8_);
          auVar9._0_8_ = -(ulong)(auVar56._0_8_ < auVar51._0_8_);
          auVar51 = auVar51 ^ (auVar51 ^ auVar56) & ~auVar9;
          auVar57._0_8_ = -(ulong)(auVar53._0_8_ < auVar51._0_8_);
          auVar57._8_8_ = -(ulong)(auVar53._8_8_ < auVar51._8_8_);
          auVar51 = auVar51 ^ (auVar51 ^ auVar53) & ~auVar57;
          auVar54._0_8_ = -(ulong)(auVar55._0_8_ < auVar51._0_8_);
          auVar54._8_8_ = -(ulong)(auVar55._8_8_ < auVar51._8_8_);
          auVar51 = auVar51 ^ (auVar51 ^ auVar55) & ~auVar54;
          auVar53 = NEON_ext(auVar51,auVar51,8,1);
          local_130[2] = auVar51._0_8_;
          local_130[2] = local_130[2] ^
                         (local_130[2] ^ auVar53._0_8_) & ~-(ulong)(auVar53._0_8_ < local_130[2]);
          auVar52._0_8_ = -(ulong)(auVar45._0_8_ < auVar49._0_8_);
          auVar52._8_8_ = -(ulong)(auVar45._8_8_ < auVar49._8_8_);
          auVar45 = auVar45 ^ (auVar45 ^ auVar49) & ~auVar52;
          auVar50._0_8_ = -(ulong)(auVar45._0_8_ < auVar47._0_8_);
          auVar50._8_8_ = -(ulong)(auVar45._8_8_ < auVar47._8_8_);
          auVar45 = auVar45 ^ (auVar45 ^ auVar47) & ~auVar50;
          auVar48._0_8_ = -(ulong)(auVar45._0_8_ < auVar46._0_8_);
          auVar48._8_8_ = -(ulong)(auVar45._8_8_ < auVar46._8_8_);
          auVar45 = auVar45 ^ (auVar45 ^ auVar46) & ~auVar48;
          auVar46 = NEON_ext(auVar45,auVar45,8,1);
          local_130[1] = auVar45._0_8_;
          local_130[1] = local_130[1] ^
                         (local_130[1] ^ auVar46._0_8_) & ~-(ulong)(local_130[1] < auVar46._0_8_);
        }
        lVar40 = uVar36 - lVar26;
        do {
          uVar36 = local_130[lVar26 * 3 + 1];
          if (local_130[1] <= local_130[lVar26 * 3 + 1]) {
            uVar36 = local_130[1];
          }
          uVar39 = local_130[lVar26 * 3 + 2];
          if (local_130[lVar26 * 3 + 2] <= local_130[2]) {
            uVar39 = local_130[2];
          }
          lVar26 = lVar26 + 1;
          lVar40 = lVar40 + -1;
          local_130[2] = uVar39;
          local_130[1] = uVar36;
        } while (lVar40 != 0);
        uVar41 = 0;
        uVar36 = 1;
        local_130[0] = 0;
      } while (param_1 != puVar42);
      goto LAB_fffffff00a29c6dc;
    }
LAB_fffffff00a29cf7c:
    bVar23 = 0;
joined_r0xfffffff00a29cef4:
    if (uVar35 == 0) goto LAB_fffffff00a29cf38;
    uVar35 = param_1[0x3a];
    uVar38 = uVar35 - 1;
    param_1[0x3a] = uVar38;
    if (uVar35 == 0) goto LAB_fffffff00a29d04c;
  }
  else {
    if (puVar42 != (uint *)0x0 && puVar42 != param_1) {
      FUN_fffffff00a1f6fdc(puVar42 + 2);
      FUN_fffffff00a2d2ef0(puVar42);
      FUN_fffffff00a2d57b8(param_1);
    }
    if (uVar35 == 0) {
      bVar23 = 0;
      goto LAB_fffffff00a29cf38;
    }
    uVar35 = param_1[0x3a];
    uVar38 = uVar35 - 1;
    param_1[0x3a] = uVar38;
    if (uVar35 == 0) {
LAB_fffffff00a29d04c:
                    /* WARNING: Subroutine does not return */
      FUN_fffffff00aa2c834("vm_object_pl_req_end(%p): underflow\n @%s:%d");
    }
    bVar23 = 0;
  }
  if (uVar38 == 0) {
    uVar35 = param_1[0x1d];
    if ((uVar35 & 1) != 0) {
      FUN_fffffff00a216478(param_1,0,0);
      uVar35 = param_1[0x1d];
    }
    param_1[0x1d] = uVar35 & 0xfffffffe;
  }
LAB_fffffff00a29cf38:
  if (DAT_fffffff00ad10000 != local_130[0x18]) {
                    /* WARNING: Subroutine does not return */
    FUN_fffffff00aa2bc3c(bVar23);
  }
  return;
LAB_fffffff00a29c1a4:
  if (iVar24 == 5) {
    local_148 = CONCAT44(3,(undefined4)local_148);
    FUN_fffffff00a2d57b8(puVar42);
    uVar38 = (ushort)puVar42[0x1b] + 1;
    *(short *)(puVar42 + 0x1b) = (short)uVar38;
    if (uVar38 >> 0x10 != 0) goto LAB_fffffff00a29cfac;
  }
  else {
    if (iVar24 != 6) {
LAB_fffffff00a29cfb8:
                    /* WARNING: Subroutine does not return */
      FUN_fffffff00aa2c834("vm_object_update: unexpected error 0x%x from vm_fault_page()\n @%s:%d");
    }
    local_148 = CONCAT44(3,(undefined4)local_148);
  }
LAB_fffffff00a29c0d0:
  uVar43 = uVar43 + 0x4000;
  if (uVar36 <= uVar43) goto LAB_fffffff00a29c2cc;
  goto LAB_fffffff00a29c0dc;
LAB_fffffff00a29c2cc:
  uVar38 = (uint)(ushort)puVar42[0x1b];
LAB_fffffff00a29c2dc:
  uVar37 = (uVar38 & 0xffff) - 1;
  *(short *)(puVar42 + 0x1b) = (short)uVar37;
  if (0xffff < uVar37) {
LAB_fffffff00a29cffc:
                    /* WARNING: Subroutine does not return */
    FUN_fffffff00aa2c834("vm_object_paging_end(%p): underflow\n @%s:%d");
  }
  uVar37 = uVar37 & 0xffff;
  uVar33 = puVar42[0x1d];
  if (((uVar33 >> 0xc & 1) == 0) &&
     (((*(byte *)((long)puVar42 + 0xa9) & (uVar38 & 0xffff) == 0x40) != 0 ||
      ((uVar38 & 0xffff) == 0x10)))) {
    if ((uVar33 >> 6 & 1) != 0) {
      lVar26 = tpidr_el1;
      plVar27 = (long *)(DAT_fffffff00acee458 + (ulong)*(ushort *)(lVar26 + 0x1a8) * 0x4000);
      lVar26 = *plVar27;
      *plVar27 = lVar26 + 1;
      FUN_fffffff00a216478(lVar26,(long)puVar42 + 6,0,0);
      uVar33 = puVar42[0x1d];
      uVar37 = (uint)(ushort)puVar42[0x1b];
    }
    uVar33 = uVar33 & 0xffffffbf;
    puVar42[0x1d] = uVar33;
  }
  if (uVar37 == 0) {
    if ((uVar33 >> 5 & 1) != 0) {
      FUN_fffffff00a216478((long)puVar42 + 5,0,0);
      uVar33 = puVar42[0x1d];
    }
    uVar38 = uVar33 & 0xffffffdf;
    puVar42[0x1d] = uVar38;
    if (puVar42[0x1c] == 0) {
      if ((uVar33 >> 2 & 1) != 0) {
        FUN_fffffff00a216478((long)puVar42 + 2,0,0);
        uVar38 = puVar42[0x1d];
      }
      puVar42[0x1d] = uVar38 & 0xfffffffb;
    }
  }
  goto LAB_fffffff00a29c3b8;
LAB_fffffff00a29c7bc:
  uVar41 = uVar41 + 0x4000;
  if (uVar39 <= uVar41) goto LAB_fffffff00a29ccec;
  goto LAB_fffffff00a29c7d0;
LAB_fffffff00a29ccec:
  lVar26 = local_140;
  local_19c = local_19c << 0xe;
  bVar23 = bVar22 | bVar23;
  if (local_140 != 0) {
    local_140 = 0;
    FUN_fffffff00a1f6fdc(lVar26 + 8);
  }
  lVar26 = *(long *)(param_1 + 0x14);
joined_r0xfffffff00a29cd24:
  if (lVar26 != 0) {
    uVar28 = tpidr_el1;
    uVar28 = FUN_fffffff00a269a54(uVar28);
    if (*(undefined **)(lVar26 + 8) == &DAT_fffffff007bbdf10) {
      uVar31 = *(undefined8 *)(lVar26 + 0x20);
    }
    else {
      uVar31 = 0;
    }
    FUN_fffffff00a236e34(uVar28,local_19c,4,uVar31);
  }
  if (iVar24 != 0) {
    FUN_fffffff00a300478(param_1,0,local_190,iVar24);
  }
  if ((uVar38 != 0) && (lVar26 = *(long *)(param_1 + 0x14), lVar26 != 0)) {
    uVar37 = (ushort)param_1[0x1b] + 1;
    *(short *)(param_1 + 0x1b) = (short)uVar37;
    if (uVar37 >> 0x10 != 0) goto LAB_fffffff00a29cfac;
    FUN_fffffff00a1f6fdc(param_1 + 2);
    (**(code **)(*(long *)(lVar26 + 8) + 0x28))(lVar26,local_198,uVar38,param_4,param_5,0,0,uVar34);
    FUN_fffffff00a2d57b8(param_1);
    uVar4 = (ushort)param_1[0x1b];
    uVar38 = uVar4 - 1;
    *(short *)(param_1 + 0x1b) = (short)uVar38;
    if (0xffff < uVar38) goto LAB_fffffff00a29cffc;
    uVar38 = uVar38 & 0xffff;
    uVar37 = param_1[0x1d];
    if (((uVar37 >> 0xc & 1) == 0) &&
       (((*(byte *)((long)param_1 + 0xa9) & uVar4 == 0x40) != 0 || (uVar4 == 0x10)))) {
      if ((uVar37 >> 6 & 1) != 0) {
        lVar26 = tpidr_el1;
        plVar44 = (long *)(DAT_fffffff00acee458 + (ulong)*(ushort *)(lVar26 + 0x1a8) * 0x4000);
        lVar26 = *plVar44;
        *plVar44 = lVar26 + 1;
        FUN_fffffff00a216478(lVar26,(long)param_1 + 6,0,0);
        uVar37 = param_1[0x1d];
        uVar38 = (uint)(ushort)param_1[0x1b];
      }
      uVar37 = uVar37 & 0xffffffbf;
      param_1[0x1d] = uVar37;
    }
    if (uVar38 == 0) {
      if ((uVar37 >> 5 & 1) != 0) {
        FUN_fffffff00a216478((long)param_1 + 5,0,0);
        uVar37 = param_1[0x1d];
      }
      uVar38 = uVar37 & 0xffffffdf;
      param_1[0x1d] = uVar38;
      if (param_1[0x1c] == 0) {
        if ((uVar37 >> 2 & 1) != 0) {
          FUN_fffffff00a216478((long)param_1 + 2,0,0);
          uVar38 = param_1[0x1d];
        }
        param_1[0x1d] = uVar38 & 0xfffffffb;
      }
    }
  }
  if (plVar27 != (long *)0x0) {
    plVar27[0x40] = 0;
    FUN_fffffff00a265344(&DAT_fffffff007c61de0);
  }
  uVar36 = uVar36 + 1;
  if (uVar36 == uVar43) goto joined_r0xfffffff00a29cef4;
  goto LAB_fffffff00a29c710;
}

