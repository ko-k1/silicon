
/* WARNING: Removing unreachable block (ram,0xfffffff00a1ea46c) */
/* WARNING: Removing unreachable block (ram,0xfffffff00a1ea37c) */

undefined8
FUN_fffffff00a1ea220
          (long param_1,uint param_2,long param_3,undefined8 param_4,uint param_5,int param_6)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  uint uVar6;
  uint uVar7;
  ulong uVar8;
  
  if ((param_2 & 0xffffc001) != 0) {
    return 4;
  }
  uVar6 = (uint)param_4;
  if (1 < param_3 + 1U) {
    if (4 < (uVar6 & 0x1fffffff) - 1) {
      return 4;
    }
    iVar2 = FUN_fffffff00a1de1a8(param_1,param_3);
    if (iVar2 == 0) {
      return 0x11;
    }
  }
  if (0x1b < param_5) {
    return 4;
  }
  if ((1 << (ulong)(param_5 & 0x1f) & 0xa03c6ffU) == 0) {
    return 4;
  }
  uVar7 = uVar6 >> 0x1d & 1;
  if ((uVar6 & 0x1fffffff) == 4) {
    uVar7 = 1;
  }
  if ((-1 < (int)uVar6) && (uVar7 != 0)) {
    return 4;
  }
  uVar5 = tpidr_el1;
  lVar3 = FUN_fffffff00a269a54(uVar5);
  if (((lVar3 != 0) && (lVar4 = FUN_fffffff00a268fac(lVar3), lVar4 != 0)) &&
     (uVar5 = (*pcRam00000000000001c8)(lVar4,"com.apple.private.set-exception-port"),
     (int)uVar5 == 0)) {
    return uVar5;
  }
  if (((lVar3 != 0) && (lVar3 = FUN_fffffff00a268fac(lVar3), lVar3 != 0)) &&
     (uVar5 = (*pcRam00000000000001c8)(lVar3,"com.apple.security.cs.debugger"), (int)uVar5 == 0)) {
    return uVar5;
  }
  if (param_1 == 0) {
    uVar8 = 0;
LAB_fffffff00a1ea47c:
    if ((param_3 + 1U < 2) || (DAT_fffffff007bbb028 == param_3)) goto LAB_fffffff00a1ea488;
    if (param_1 == 0) {
LAB_fffffff00a1ea4c0:
      if ((5 < (uVar6 & 0x1fffffff)) || ((1 << (ulong)(uVar6 & 0x1f) & 0x34U) == 0))
      goto LAB_fffffff00a1ea4e8;
    }
    else if (((uint)uVar8 >> 1 & 1) == 0) {
      if (((uint)uVar8 >> 9 & 1) != 0) goto LAB_fffffff00a1ea4c0;
    }
    else if ((uVar8 & 0x604) != 0) goto LAB_fffffff00a1ea4c0;
LAB_fffffff00a1ea488:
    uVar5 = 0;
  }
  else {
    uVar8 = *(ulong *)(*(long *)(param_1 + 0x310) + 0x58);
    iVar2 = FUN_fffffff00a9bd5cc(param_1,"com.apple.security.only-one-exception-port");
    if (iVar2 == 0) {
LAB_fffffff00a1ea438:
      uVar8 = *(ulong *)(*(long *)(param_1 + 0x310) + 0x58);
      goto LAB_fffffff00a1ea47c;
    }
    uVar7 = 1;
    if ((uVar8 & 4) == 0) {
      uVar7 = (uint)((uVar8 & 0x600) != 0);
    }
    uVar1 = (uint)uVar8 >> 9 & 1;
    if ((uVar8 & 2) != 0) {
      uVar1 = uVar7;
    }
    if ((uVar1 == 0) || (param_6 != 0)) goto LAB_fffffff00a1ea438;
LAB_fffffff00a1ea4e8:
    FUN_fffffff00aa2c118(param_4,param_2,6);
    uVar5 = 0x35;
  }
  return uVar5;
}

