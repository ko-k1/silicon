
undefined8 FUN_fffffff008423b1c(long param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  bool bVar1;
  int iVar2;
  undefined8 uVar3;
  char *pcVar4;
  bool bVar5;
  long lVar6;
  
  if (*(int *)(param_4 + 0x68) - 1U < 2) {
    if (*(uint *)(param_4 + 0x510) < 8) {
      if (*(uint *)(param_4 + 0x768) < 8) {
        if ((((*(uint *)(param_4 + 0x1888) < 7) && (*(uint *)(param_4 + 0x27f8) < 0x10)) &&
            (*(uint *)(param_4 + 0x2c10) < 0x11)) &&
           ((*(byte *)(param_4 + 0x42c7) < 2 && (*(uint *)(param_4 + 0x27f4) < 0x3f)))) {
          if (*(byte *)(param_4 + 0x32c0) < 0x41) {
            uVar3 = FUN_fffffff008421158(param_2,param_4 + 0x1880);
            if ((int)uVar3 != 0) {
              iVar2 = FUN_fffffff0084ddb38(0x74,4);
              if (iVar2 == 0) {
                return uVar3;
              }
              iVar2 = FUN_fffffff0084ddb80(0x74);
              FUN_fffffff0085543f8();
              FUN_fffffff0084ddbb8(4);
              if (iVar2 == 0) {
                thunk_EXT_FUN_80110000038b6e98
                          (&MACH_HEADER,PTR_DAT_fffffff007cfb808,0,
                           "%lld %d AVE %s: %s:%d %s | HEVC VPS extension layer/OLS counts are out of range %d"
                          );
                return uVar3;
              }
              pcVar4 = 
              "%lld %d AVE %s: %s:%d %s | HEVC VPS extension layer/OLS counts are out of range %d\n"
              ;
LAB_fffffff008423c48:
              thunk_EXT_FUN_80110000031fc27c(pcVar4);
              return uVar3;
            }
            lVar6 = 0;
            bVar1 = true;
            do {
              bVar5 = bVar1;
              lVar6 = param_4 + 0x4350 + lVar6 * 0x1c74;
              if ((6 < *(uint *)(lVar6 + 8)) || (0x10 < *(uint *)(lVar6 + 0x1b2c))) {
                iVar2 = FUN_fffffff0084ddb38(0x74,4);
                if (iVar2 == 0) {
                  return 0xfffffc17;
                }
                iVar2 = FUN_fffffff0084ddb80(0x74);
                FUN_fffffff0085543f8();
                FUN_fffffff0084ddbb8(4);
                if (iVar2 == 0) {
                  thunk_EXT_FUN_80110000038b6e98
                            (&MACH_HEADER,PTR_DAT_fffffff007cfb808,0,
                             "%lld %d AVE %s: %s:%d %s | HEVC SPS count is out of range %d %d %d %d %d"
                            );
                  return 0xfffffc17;
                }
                pcVar4 = 
                "%lld %d AVE %s: %s:%d %s | HEVC SPS count is out of range %d %d %d %d %d\n";
                goto LAB_fffffff008423e60;
              }
              if (0xc < *(uint *)(lVar6 + 500)) {
                iVar2 = FUN_fffffff0084ddb38(0x74,4);
                if (iVar2 == 0) {
                  return 0xfffffc17;
                }
                iVar2 = FUN_fffffff0084ddb80(0x74);
                FUN_fffffff0085543f8();
                FUN_fffffff0084ddbb8(4);
                if (iVar2 == 0) {
                  thunk_EXT_FUN_80110000038b6e98
                            (&MACH_HEADER,PTR_DAT_fffffff007cfb808,0,
                             "%lld %d AVE %s: %s:%d %s | HEVC log2_max_pic_order_cnt_lsb_minus4 is out of range %d %d %d (max %d)"
                            );
                  return 0xfffffc17;
                }
                pcVar4 = 
                "%lld %d AVE %s: %s:%d %s | HEVC log2_max_pic_order_cnt_lsb_minus4 is out of range %d %d %d (max %d)\n"
                ;
                goto LAB_fffffff008423e60;
              }
              lVar6 = 1;
              bVar1 = false;
            } while (bVar5);
            if (*(uint *)(param_4 + 0x5e0) < 3) {
              uVar3 = FUN_fffffff00843763c
                                (param_2,3,0,*(undefined4 *)(param_4 + 0x3c),
                                 *(undefined4 *)(param_4 + 0x40),1);
              if ((int)uVar3 != 0) {
                iVar2 = FUN_fffffff0084ddb38(0x74,4);
                if (iVar2 == 0) {
                  return uVar3;
                }
                iVar2 = FUN_fffffff0084ddb80(0x74);
                FUN_fffffff0085543f8();
                FUN_fffffff0084ddbb8(4);
                if (iVar2 == 0) {
                  thunk_EXT_FUN_80110000038b6e98
                            (&MACH_HEADER,PTR_DAT_fffffff007cfb808,0,
                             "%lld %d AVE %s: %s:%d %s | frame dimension is out of range %d %d %d");
                  return uVar3;
                }
                pcVar4 = "%lld %d AVE %s: %s:%d %s | frame dimension is out of range %d %d %d\n";
                goto LAB_fffffff008423c48;
              }
              if (*(uint *)(param_4 + 0x420) < 0x15) {
                if (((*(int *)(param_1 + 0x1b84) == 0) ||
                    (*(int *)(param_1 + 0x1b84) == *(int *)(param_4 + 0x3c))) &&
                   ((*(int *)(param_1 + 0x1b88) == 0 ||
                    (*(int *)(param_1 + 0x1b88) == *(int *)(param_4 + 0x40))))) {
                  uVar3 = FUN_fffffff008566fc0(*(undefined8 *)(param_1 + 0x38));
                  uVar3 = FUN_fffffff0085492c0(uVar3,param_4 + 0x1658);
                  if ((int)uVar3 == 0) {
                    return uVar3;
                  }
                  iVar2 = FUN_fffffff0084ddb38(0x74,4);
                  if (iVar2 == 0) {
                    return uVar3;
                  }
                  iVar2 = FUN_fffffff0084ddb80(0x74);
                  FUN_fffffff0085543f8();
                  FUN_fffffff0084ddbb8(4);
                  if (iVar2 == 0) {
                    thunk_EXT_FUN_80110000038b6e98
                              (&MACH_HEADER,PTR_DAT_fffffff007cfb808,0,
                               "%lld %d AVE %s: %s:%d %s | wrong DLB configuration %p %lld %d");
                    return uVar3;
                  }
                  pcVar4 = "%lld %d AVE %s: %s:%d %s | wrong DLB configuration %p %lld %d\n";
                  goto LAB_fffffff008423c48;
                }
                iVar2 = FUN_fffffff0084ddb38(0x74,4);
                if (iVar2 == 0) {
                  return 0xfffffc17;
                }
                iVar2 = FUN_fffffff0084ddb80(0x74);
                FUN_fffffff0085543f8();
                FUN_fffffff0084ddbb8(4);
                if (iVar2 == 0) {
                  thunk_EXT_FUN_80110000038b6e98
                            (&MACH_HEADER,PTR_DAT_fffffff007cfb808,0,
                             "%lld %d AVE %s: %s:%d %s | frame dimension doesn\'t match between prepare [%d %d] and start [%d %d] %p %lld %d"
                            );
                  return 0xfffffc17;
                }
                pcVar4 = 
                "%lld %d AVE %s: %s:%d %s | frame dimension doesn\'t match between prepare [%d %d] and start [%d %d] %p %lld %d\n"
                ;
              }
              else {
                iVar2 = FUN_fffffff0084ddb38(0x74,4);
                if (iVar2 == 0) {
                  return 0xfffffc17;
                }
                iVar2 = FUN_fffffff0084ddb80(0x74);
                FUN_fffffff0085543f8();
                FUN_fffffff0084ddbb8(4);
                if (iVar2 == 0) {
                  thunk_EXT_FUN_80110000038b6e98
                            (&MACH_HEADER,PTR_DAT_fffffff007cfb808,0,
                             "%lld %d AVE %s: %s:%d %s | LookAhead frame count is out of range %p %lld %d %d"
                            );
                  return 0xfffffc17;
                }
                pcVar4 = 
                "%lld %d AVE %s: %s:%d %s | LookAhead frame count is out of range %p %lld %d %d\n";
              }
            }
            else {
              iVar2 = FUN_fffffff0084ddb38(0x74,4);
              if (iVar2 == 0) {
                return 0xfffffc17;
              }
              iVar2 = FUN_fffffff0084ddb80(0x74);
              FUN_fffffff0085543f8();
              FUN_fffffff0084ddbb8(4);
              if (iVar2 == 0) {
                thunk_EXT_FUN_80110000038b6e98
                          (&MACH_HEADER,PTR_DAT_fffffff007cfb808,0,
                           "%lld %d AVE %s: %s:%d %s | MCTF strength count out of range %p %lld %d [0 %d]"
                          );
                return 0xfffffc17;
              }
              pcVar4 = 
              "%lld %d AVE %s: %s:%d %s | MCTF strength count out of range %p %lld %d [0 %d]\n";
            }
          }
          else {
            iVar2 = FUN_fffffff0084ddb38(0x74,4);
            if (iVar2 == 0) {
              return 0xfffffc17;
            }
            iVar2 = FUN_fffffff0084ddb80(0x74);
            FUN_fffffff0085543f8();
            FUN_fffffff0084ddbb8(4);
            if (iVar2 == 0) {
              thunk_EXT_FUN_80110000038b6e98
                        (&MACH_HEADER,PTR_DAT_fffffff007cfb808,0,
                         "%lld %d AVE %s: %s:%d %s | HEVC VPS num_add_layer_sets is out of range %d %d %d"
                        );
              return 0xfffffc17;
            }
            pcVar4 = 
            "%lld %d AVE %s: %s:%d %s | HEVC VPS num_add_layer_sets is out of range %d %d %d\n";
          }
        }
        else {
          iVar2 = FUN_fffffff0084ddb38(0x74,4);
          if (iVar2 == 0) {
            return 0xfffffc17;
          }
          iVar2 = FUN_fffffff0084ddb80(0x74);
          FUN_fffffff0085543f8();
          FUN_fffffff0084ddbb8(4);
          if (iVar2 == 0) {
            thunk_EXT_FUN_80110000038b6e98
                      (&MACH_HEADER,PTR_DAT_fffffff007cfb808,0,
                       "%lld %d AVE %s: %s:%d %s | HEVC VPS count is out of range %d %d %d %d %d %d"
                      );
            return 0xfffffc17;
          }
          pcVar4 = "%lld %d AVE %s: %s:%d %s | HEVC VPS count is out of range %d %d %d %d %d %d\n";
        }
      }
      else {
        iVar2 = FUN_fffffff0084ddb38(0x74,4);
        if (iVar2 == 0) {
          return 0xfffffc17;
        }
        iVar2 = FUN_fffffff0084ddb80(0x74);
        FUN_fffffff0085543f8();
        FUN_fffffff0084ddbb8(4);
        if (iVar2 == 0) {
          thunk_EXT_FUN_80110000038b6e98
                    (&MACH_HEADER,PTR_DAT_fffffff007cfb808,0,
                     "%lld %d AVE %s: %s:%d %s | number of temporal layers (prop) is out of range %d %d %d"
                    );
          return 0xfffffc17;
        }
        pcVar4 = 
        "%lld %d AVE %s: %s:%d %s | number of temporal layers (prop) is out of range %d %d %d\n";
      }
    }
    else {
      iVar2 = FUN_fffffff0084ddb38(0x74,4);
      if (iVar2 == 0) {
        return 0xfffffc17;
      }
      iVar2 = FUN_fffffff0084ddb80(0x74);
      FUN_fffffff0085543f8();
      FUN_fffffff0084ddbb8(4);
      if (iVar2 == 0) {
        thunk_EXT_FUN_80110000038b6e98
                  (&MACH_HEADER,PTR_DAT_fffffff007cfb808,0,
                   "%lld %d AVE %s: %s:%d %s | number of sub layer is out of range %d %d %d");
        return 0xfffffc17;
      }
      pcVar4 = "%lld %d AVE %s: %s:%d %s | number of sub layer is out of range %d %d %d\n";
    }
  }
  else {
    iVar2 = FUN_fffffff0084ddb38(0x74,4);
    if (iVar2 == 0) {
      return 0xfffffc17;
    }
    iVar2 = FUN_fffffff0084ddb80(0x74);
    FUN_fffffff0085543f8();
    FUN_fffffff0084ddbb8(4);
    if (iVar2 == 0) {
      thunk_EXT_FUN_80110000038b6e98
                (&MACH_HEADER,PTR_DAT_fffffff007cfb808,0,
                 "%lld %d AVE %s: %s:%d %s | layer number is out of range %d %d (%d, %d]");
      return 0xfffffc17;
    }
    pcVar4 = "%lld %d AVE %s: %s:%d %s | layer number is out of range %d %d (%d, %d]\n";
  }
LAB_fffffff008423e60:
  thunk_EXT_FUN_80110000031fc27c(pcVar4);
  return 0xfffffc17;
}

