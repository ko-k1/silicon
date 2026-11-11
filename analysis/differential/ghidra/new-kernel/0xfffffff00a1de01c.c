
/* WARNING: Removing unreachable block (ram,0xfffffff00a1de0f4) */
/* WARNING: Removing unreachable block (ram,0xfffffff00a1de08c) */

uint FUN_fffffff00a1de01c(long param_1,long param_2)

{
  uint uVar1;
  code *pcVar2;
  uint uVar3;
  int iVar4;
  undefined8 uVar5;
  ulong uVar6;
  uint uVar7;
  undefined8 uVar8;
  
  uVar7 = 1;
  if ((param_1 == 0) || (DAT_fffffff007bbb028 == param_2)) goto LAB_fffffff00a1de184;
  uVar8 = *(undefined8 *)(*(long *)(param_1 + 0x310) + 0x58);
  uVar3 = FUN_fffffff00a1b9b38(param_2);
  if ((*(byte *)(param_2 + 2) & 1) == 0) {
                    /* WARNING: Does not return */
    pcVar2 = (code *)SoftwareBreakpoint(0xbffc,0xfffffff00a1de1a8);
    (*pcVar2)();
  }
  uVar1 = uVar3 & 0xff;
  *(undefined1 *)(param_2 + 2) = 0;
  FUN_fffffff00a1f7934(param_2 + 0x14);
  if (((uint)uVar8 >> 3 & 1) == 0) goto LAB_fffffff00a1de0bc;
  uVar8 = *(undefined8 *)(param_1 + 0x310);
  uVar7 = 1;
  if ((uVar1 == 2) || (uVar1 == 8)) goto LAB_fffffff00a1de184;
  FUN_fffffff00a268fac(param_1);
  iVar4 = FUN_fffffff00a73c3b4();
  if (iVar4 == 0) {
LAB_fffffff00a1de0bc:
    if (8 < uVar1) {
      uVar7 = 0;
      goto LAB_fffffff00a1de184;
    }
  }
  else {
    uVar5 = tpidr_el1;
    uVar5 = FUN_fffffff00a269a54(uVar5);
    iVar4 = FUN_fffffff00a9bd5cc(uVar5,"com.apple.private.set-exception-port");
    if ((iVar4 != 0) ||
       (iVar4 = FUN_fffffff00a9bd5cc(uVar5,"com.apple.security.cs.debugger"), iVar4 != 0))
    goto LAB_fffffff00a1de0bc;
    uVar6 = FUN_fffffff00a1b81a8(0xd,uVar8,0,0,param_2,0);
    uVar7 = 0;
    if (((uVar6 & 1) != 0) || (8 < uVar1)) goto LAB_fffffff00a1de184;
  }
  uVar7 = 0x116 >> (ulong)(uVar3 & 0x1f);
LAB_fffffff00a1de184:
  return uVar7 & 1;
}

