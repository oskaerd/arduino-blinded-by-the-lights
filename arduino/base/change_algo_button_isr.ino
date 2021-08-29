void ChangeAlgoButtonIsr(void)
{
    gCurrentLedFuncIdx++;
    gCurrentLedFuncIdx %= RBG_CONTROL_CBS_COUNT;
}
