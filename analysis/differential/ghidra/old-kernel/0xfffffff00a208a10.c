
/* WARNING: Removing unreachable block (ram,0xfffffff00a208b54) */
/* WARNING: Removing unreachable block (ram,0xfffffff00a208c68) */
/* WARNING: Removing unreachable block (ram,0xfffffff00a208ab8) */
/* WARNING: Type propagation algorithm not settling */

undefined8
FUN_fffffff00a208a10
          (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,undefined8 param_5,
          undefined8 param_6,ulong param_7,long param_8)

{
  ulong *puVar1;
  byte bVar2;
  short sVar3;
  int iVar4;
  long lVar5;
  long lVar6;
  undefined8 uVar7;
  ulong uVar8;
  uint uVar9;
  uint uVar10;
  int in_wzr;
  
  if (param_1 == 0) {
    return 4;
  }
  if ((((uint)param_7 >> 9 & 1) != 0) || (*(short *)(param_1 + 200) < 0)) {
    uVar7 = tpidr_el1;
    lVar5 = FUN_fffffff00a22d63c(uVar7);
    lVar6 = FUN_fffffff00a22d63c(param_1);
    uVar7 = FUN_fffffff00a22cb94();
    uVar8 = *(ulong *)(*(long *)(lVar6 + 0x310) + 0x58);
    uVar10 = (uint)uVar8;
    if ((uVar8 & 1) != 0) {
      if ((*(short *)(param_1 + 200) < 0) && (lVar6 != lVar5)) {
        if ((uVar10 >> 1 & 1) == 0) {
          if ((uVar10 >> 9 & 1) != 0) goto LAB_fffffff00a208afc;
        }
        else if ((uVar8 & 0x604) != 0) {
LAB_fffffff00a208afc:
          FUN_fffffff00a22cb94(lVar6);
          iVar4 = FUN_fffffff00a6fcdb8();
          if ((iVar4 != 0) &&
             (iVar4 = FUN_fffffff00a97d030(lVar5,"com.apple.private.thread-set-state"), iVar4 == 0))
          goto LAB_fffffff00a208c9c;
        }
      }
      if ((param_8 != 0) &&
         ((*(short *)(param_1 + 200) < 0 &&
          (*(int *)(param_8 + 0x14) != *(int *)(*(long *)(lVar6 + 0x318) + 0x18))))) {
        if ((uVar10 >> 1 & 1) == 0) {
          if ((uVar10 >> 10 & 1) != 0) goto LAB_fffffff00a208c38;
        }
        else if ((uVar8 & 0x404) != 0) {
LAB_fffffff00a208c38:
          iVar4 = FUN_fffffff00a6fcdb8(uVar7);
          if (iVar4 != 0) {
            lVar5 = *(long *)(lVar6 + 0x310);
            if (lVar5 == 0) {
              lVar5 = 0;
            }
            uVar8 = FUN_fffffff00a17c1bc(0xf,lVar5,param_2,(long)*(int *)(param_8 + 0x14),0,0);
            if ((uVar8 & 1) == 0) {
                    /* WARNING: Subroutine does not return */
              FUN_fffffff00a9ebcbc
                        (
                        "Expected to deny after handling IPC security policy violation policy %d, but got %d @%s:%d"
                        );
            }
            return 8;
          }
        }
      }
      if (((uint)param_7 >> 9 & 1) != 0) {
        uVar9 = (uint)param_2;
        if (-1 < *(short *)(param_1 + 200)) {
          if ((uVar10 >> 1 & 1) == 0) {
            if ((uVar10 >> 9 & 1) != 0) goto LAB_fffffff00a208b94;
          }
          else if ((uVar8 & 0x604) != 0) {
LAB_fffffff00a208b94:
            if (((uVar9 < 10) && ((1 << (ulong)(uVar9 & 0x1f) & 0x242U) != 0)) &&
               (iVar4 = FUN_fffffff00a97d030(lVar5,"com.apple.private.thread-set-state"), iVar4 == 0
               )) goto LAB_fffffff00a208c9c;
          }
        }
        iVar4 = FUN_fffffff00a1fc894(lVar6);
        if (((iVar4 != 0) && (uVar9 < 0x10)) &&
           (((1 << (ulong)(uVar9 & 0x1f) & 0xc010U) != 0 &&
            (iVar4 = FUN_fffffff00a97d030(lVar5,"com.apple.private.thread-set-state"), iVar4 == 0)))
           ) {
LAB_fffffff00a208c9c:
          FUN_fffffff00a9eb5a0(param_2,0,5);
          return 8;
        }
      }
    }
  }
  lVar5 = tpidr_el1;
  if (*(ulong *)(param_1 + 0x430) == 0) {
    *(ulong *)(param_1 + 0x430) = (ulong)*(uint *)(lVar5 + 0x4e0);
    bVar2 = *(byte *)(param_1 + 0x423);
  }
  else {
    FUN_fffffff00a1b6050(param_1 + 0x428,lVar5,0);
    bVar2 = *(byte *)(param_1 + 0x423);
  }
  if ((bVar2 & 1) == 0) {
    uVar7 = 0x25;
    goto LAB_fffffff00a208e50;
  }
  if (((param_7 & 1) != 0) &&
     (uVar7 = FUN_fffffff00a330514(param_1,param_2,param_3,param_4,param_5,param_6,param_7),
     (int)uVar7 != 0)) goto LAB_fffffff00a208e50;
  if (param_1 == lVar5) {
    uVar7 = FUN_fffffff00a3318e0(param_1,param_2,param_3,param_4);
  }
  else {
    sVar3 = *(short *)(param_1 + 0x208);
    *(short *)(param_1 + 0x208) = sVar3 + 1;
    if ((sVar3 == 0) && (FUN_fffffff00a2077a8(param_1), (DAT_fffffff00ad38a18 & 0xfffffff7) != 0)) {
      lVar6 = FUN_fffffff00a22d63c(param_1);
      FUN_fffffff00a673598
                (0x1210008,*(undefined8 *)(param_1 + 0x4d8),(long)*(int *)(param_1 + 0x3c0),
                 *(byte *)(lVar6 + 0x3f2) & 1,0);
    }
    puVar1 = (ulong *)(param_1 + 0x430);
    if (*(int *)puVar1 == *(int *)(lVar5 + 0x4e0)) {
      *(int *)puVar1 = in_wzr;
    }
    else {
      FUN_fffffff00a1b6b90(param_1 + 0x428,lVar5);
    }
    iVar4 = FUN_fffffff00a1db78c(param_1,1);
    if (*puVar1 == 0) {
      *puVar1 = (ulong)*(uint *)(lVar5 + 0x4e0);
      if (iVar4 == 0) goto LAB_fffffff00a208dd8;
LAB_fffffff00a208d60:
      uVar7 = FUN_fffffff00a3318e0(param_1,param_2,param_3,param_4);
      FUN_fffffff00a1dbb1c(param_1);
      sVar3 = *(short *)(param_1 + 0x208);
    }
    else {
      FUN_fffffff00a1b6050(param_1 + 0x428,lVar5,0);
      if (iVar4 != 0) goto LAB_fffffff00a208d60;
LAB_fffffff00a208dd8:
      uVar7 = 0xe;
      sVar3 = *(short *)(param_1 + 0x208);
    }
    if ((sVar3 != 0) && (*(short *)(param_1 + 0x208) = sVar3 + -1, sVar3 == 1)) {
      bVar2 = *(byte *)(param_1 + 0x423);
      if ((bVar2 >> 2 & 1) == 0) {
        FUN_fffffff00a206fe8(param_1);
      }
      else if ((bVar2 >> 6 & 1) != 0) {
        *(byte *)(param_1 + 0x423) = bVar2 & 0xbf;
        FUN_fffffff00a1db68c(param_1 + 0x208,param_1);
      }
      if ((DAT_fffffff00ad38a18 & 0xfffffff7) != 0) {
        FUN_fffffff00a673598(0x121000c,*(undefined8 *)(param_1 + 0x4d8),0,0,0);
      }
    }
  }
  if (((param_7 & 1) != 0) && ((int)uVar7 == 0)) {
    FUN_fffffff00a1a2124(param_1);
    uVar7 = 0;
  }
LAB_fffffff00a208e50:
  if (*(int *)(param_1 + 0x430) == *(int *)(lVar5 + 0x4e0)) {
    *(int *)(param_1 + 0x430) = in_wzr;
  }
  else {
    FUN_fffffff00a1b6b90(param_1 + 0x428,lVar5);
  }
  return uVar7;
}

