
/* WARNING: Removing unreachable block (ram,0xfffffff00a244f68) */
/* WARNING: Removing unreachable block (ram,0xfffffff00a2450a4) */
/* WARNING: Removing unreachable block (ram,0xfffffff00a244ea8) */
/* WARNING: Type propagation algorithm not settling */

undefined8
FUN_fffffff00a244dc8
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          undefined4 param_6,ulong param_7,long param_8)

{
  ulong *puVar1;
  byte bVar2;
  short sVar3;
  int iVar4;
  undefined8 uVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  uint uVar9;
  uint uVar10;
  int in_wzr;
  
  if (param_1 == 0) {
    return 4;
  }
  if ((param_7 & 1) != 0) {
    uVar5 = FUN_fffffff00a269a54(param_1);
    iVar4 = FUN_fffffff00aa1aedc(param_8,uVar5,param_2,param_3,param_4);
    if (iVar4 != 0) {
      return 8;
    }
  }
  if ((((uint)param_7 >> 9 & 1) != 0) || (*(short *)(param_1 + 200) < 0)) {
    uVar5 = tpidr_el1;
    lVar6 = FUN_fffffff00a269a54(uVar5);
    lVar7 = FUN_fffffff00a269a54(param_1);
    uVar5 = FUN_fffffff00a268fac();
    uVar8 = *(ulong *)(*(long *)(lVar7 + 0x310) + 0x58);
    uVar10 = (uint)uVar8;
    if ((uVar8 & 1) != 0) {
      if ((*(short *)(param_1 + 200) < 0) && (lVar7 != lVar6)) {
        if ((uVar10 >> 1 & 1) == 0) {
          if ((uVar10 >> 9 & 1) != 0) goto LAB_fffffff00a244eec;
        }
        else if ((uVar8 & 0x604) != 0) {
LAB_fffffff00a244eec:
          FUN_fffffff00a268fac(lVar7);
          iVar4 = FUN_fffffff00a73c3b4();
          if (((iVar4 != 0) &&
              (iVar4 = FUN_fffffff00a9bd5cc(lVar6,"com.apple.private.thread-set-state"), iVar4 == 0)
              ) && (iVar4 = FUN_fffffff00a9bd5cc(lVar6,"com.apple.security.cs.debugger"), iVar4 == 0
                   )) goto LAB_fffffff00a2450d4;
        }
      }
      if (((param_8 != 0) && (*(short *)(param_1 + 200) < 0)) &&
         (*(int *)(param_8 + 0x14) != *(int *)(*(long *)(lVar7 + 0x318) + 0x18))) {
        if ((uVar10 >> 1 & 1) == 0) {
          if ((uVar10 >> 10 & 1) != 0) goto LAB_fffffff00a245074;
        }
        else if ((uVar8 & 0x404) != 0) {
LAB_fffffff00a245074:
          iVar4 = FUN_fffffff00a73c3b4(uVar5);
          if (iVar4 != 0) {
            lVar6 = *(long *)(lVar7 + 0x310);
            if (lVar6 == 0) {
              lVar6 = 0;
            }
            FUN_fffffff00a1b8958(0xf,lVar6,param_2,(long)*(int *)(param_8 + 0x14),0,0);
            return 8;
          }
        }
      }
      if (((uint)param_7 >> 9 & 1) != 0) {
        uVar9 = (uint)param_2;
        if (-1 < *(short *)(param_1 + 200)) {
          if ((uVar10 >> 1 & 1) == 0) {
            if ((uVar10 >> 9 & 1) != 0) goto LAB_fffffff00a244fa8;
          }
          else if ((uVar8 & 0x604) != 0) {
LAB_fffffff00a244fa8:
            if (((uVar9 < 10) && ((1 << (ulong)(uVar9 & 0x1f) & 0x242U) != 0)) &&
               ((iVar4 = FUN_fffffff00a9bd5cc(lVar6,"com.apple.private.thread-set-state"),
                iVar4 == 0 &&
                (iVar4 = FUN_fffffff00a9bd5cc(lVar6,"com.apple.security.cs.debugger"), iVar4 == 0)))
               ) goto LAB_fffffff00a2450d4;
          }
        }
        iVar4 = FUN_fffffff00a238c4c(lVar7);
        if ((((iVar4 != 0) && (uVar9 < 0x10)) && ((1 << (ulong)(uVar9 & 0x1f) & 0xc010U) != 0)) &&
           ((iVar4 = FUN_fffffff00a9bd5cc(lVar6,"com.apple.private.thread-set-state"), iVar4 == 0 &&
            (iVar4 = FUN_fffffff00a9bd5cc(lVar6,"com.apple.security.cs.debugger"), iVar4 == 0)))) {
LAB_fffffff00a2450d4:
          FUN_fffffff00aa2c118(param_2,0,5);
          return 8;
        }
      }
    }
  }
  lVar6 = tpidr_el1;
  if (*(ulong *)(param_1 + 0x430) == 0) {
    *(ulong *)(param_1 + 0x430) = (ulong)*(uint *)(lVar6 + 0x4e0);
    bVar2 = *(byte *)(param_1 + 0x423);
  }
  else {
    FUN_fffffff00a1f2328(param_1 + 0x428,lVar6,0);
    bVar2 = *(byte *)(param_1 + 0x423);
  }
  if ((bVar2 & 1) == 0) {
    uVar5 = 0x25;
    goto LAB_fffffff00a245288;
  }
  if (((param_7 & 1) != 0) &&
     (uVar5 = FUN_fffffff00a36d308(param_1,param_2,param_3,param_4,param_5,param_6,param_7),
     (int)uVar5 != 0)) goto LAB_fffffff00a245288;
  if (param_1 == lVar6) {
    uVar5 = FUN_fffffff00a36e6d4(param_1,param_2,param_3,param_4);
  }
  else {
    sVar3 = *(short *)(param_1 + 0x208);
    *(short *)(param_1 + 0x208) = sVar3 + 1;
    if ((sVar3 == 0) && (FUN_fffffff00a243b60(param_1), (DAT_fffffff00ad78af8 & 0xfffffff7) != 0)) {
      lVar7 = FUN_fffffff00a269a54(param_1);
      FUN_fffffff00a6b2b1c
                (0x1210008,*(undefined8 *)(param_1 + 0x4d8),(long)*(int *)(param_1 + 0x3c0),
                 *(byte *)(lVar7 + 0x3f2) & 1,0);
    }
    puVar1 = (ulong *)(param_1 + 0x430);
    if (*(int *)puVar1 == *(int *)(lVar6 + 0x4e0)) {
      *(int *)puVar1 = in_wzr;
    }
    else {
      FUN_fffffff00a1f2e68(param_1 + 0x428,lVar6);
    }
    iVar4 = FUN_fffffff00a217b1c(param_1,1);
    if (*puVar1 == 0) {
      *puVar1 = (ulong)*(uint *)(lVar6 + 0x4e0);
      if (iVar4 == 0) goto LAB_fffffff00a245210;
LAB_fffffff00a245198:
      uVar5 = FUN_fffffff00a36e6d4(param_1,param_2,param_3,param_4);
      FUN_fffffff00a217eac(param_1);
      sVar3 = *(short *)(param_1 + 0x208);
    }
    else {
      FUN_fffffff00a1f2328(param_1 + 0x428,lVar6,0);
      if (iVar4 != 0) goto LAB_fffffff00a245198;
LAB_fffffff00a245210:
      uVar5 = 0xe;
      sVar3 = *(short *)(param_1 + 0x208);
    }
    if ((sVar3 != 0) && (*(short *)(param_1 + 0x208) = sVar3 + -1, sVar3 == 1)) {
      bVar2 = *(byte *)(param_1 + 0x423);
      if ((bVar2 >> 2 & 1) == 0) {
        FUN_fffffff00a2433a0(param_1);
      }
      else if ((bVar2 >> 6 & 1) != 0) {
        *(byte *)(param_1 + 0x423) = bVar2 & 0xbf;
        FUN_fffffff00a217a1c(param_1 + 0x208,param_1);
      }
      if ((DAT_fffffff00ad78af8 & 0xfffffff7) != 0) {
        FUN_fffffff00a6b2b1c(0x121000c,*(undefined8 *)(param_1 + 0x4d8),0,0,0);
      }
    }
  }
  if (((param_7 & 1) != 0) && ((int)uVar5 == 0)) {
    FUN_fffffff00a1de434(param_1);
    uVar5 = 0;
  }
LAB_fffffff00a245288:
  if (*(int *)(param_1 + 0x430) == *(int *)(lVar6 + 0x4e0)) {
    *(int *)(param_1 + 0x430) = in_wzr;
  }
  else {
    FUN_fffffff00a1f2e68(param_1 + 0x428,lVar6);
  }
  return uVar5;
}

