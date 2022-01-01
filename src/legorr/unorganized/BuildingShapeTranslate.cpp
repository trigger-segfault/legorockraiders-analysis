
def sb(direction):
    signBit = ((direction + 0x8000) & 0xffffffff) >> 31
    result = (((((direction + 0x8000) & 0xffffffff) ^ signBit) - signBit & 3 ^ signBit) - signBit) & 0xffffffff
    return (signBit, result)

Point2I* __cdecl lego::game::Game_RotateBuildingShape(const Point2I* position, const Point2I* shapePoints, int shapeCount, Direction direction)
{
  // positive direction MODULUS 4
  Direction posDirection = (Direction)((int)direction % (int)DIRECTION__COUNT);
  if ((int)posDirection < 0)
      posDirection += (int)DIRECTION__COUNT;

  int swapPoint_x = 0; // dummy initialize
  // uint signBit = (int)(param_4 + 0x8000U) >> 0x1f;
  // pPVar1 = globals::tmp_RotateBuildingShapePoints;
  for (int i = 0; i < count; i++) {
    Point2I* dstPoint = &globals::tmp_RotateBuildingShapePoints[i];
    dstPoint->x = shapePoints[i].x;
    dstPoint->y = shapePoints[i].y;
    // pPVar1->x = *(int *)((int)&pPVar1[-0xa0479].x + param_2);
    // pPVar1->y = *(int *)(param_2 + -0x5023c4 + (int)pPVar1);
    //0x005023cc
    //0x005023d0
                    /* unsigned modulus (direction % 4) */
    if (true) {
      // switch(((param_4 + 0x8000U ^ signBit) - signBit & 3 ^ signBit) - signBit) {
      switch(posDirection) {
      case DIRECTION_UP:    // (x, y)
        break; // no change
        //goto switchD_0046441a_caseD_0;
      case DIRECTION_RIGHT: // (-y, x)
		swapPoint_x = dstPoint->x;
		dstPoint->x = -dstPoint->y;
		dstPoint->y =  swapPoint_x;
        break;
        //goto LAB_00464440;
      case DIRECTION_DOWN:  // (-x, -y)
		dstPoint->x = -dstPoint->x;
		dstPoint->y = -dstPoint->y;
        break;
      case DIRECTION_LEFT:  // (y, -x)
		swapPoint_x = dstPoint->x;
		dstPoint->x =  dstPoint->y;
		dstPoint->y = -swapPoint_x;
        break;
      default:
        break; // no change
      }
      iVar3 = -iVar3;
LAB_00464440:
      dstPoint->y = iVar3;
    }
switchD_0046441a_caseD_0:
    dstPoint->x += position->x;
    dstPoint->y += position->y;
  }
  return globals::tmp_RotateBuildingShapePoints;


  Point2I *pPVar1;
  uint uVar2;
  int iVar3;

  if (count != 0) {
    uVar2 = (int)(param_4 + 0x8000U) >> 0x1f;
    pPVar1 = Point2I_ARRAY_005023c8;
    do {
      pPVar1->x = *(int *)((int)&pPVar1[-0xa0479].x + param_2);
      pPVar1->y = *(int *)(param_2 + -0x5023c4 + (int)pPVar1);
      if (true) {
        switch(((param_4 + 0x8000U ^ uVar2) - uVar2 & 3 ^ uVar2) - uVar2) {
        default:
          goto switchD_0046441a_caseD_0;
        case 1:
          iVar3 = pPVar1->x;
          pPVar1->x = -pPVar1->y;
          goto LAB_00464440;
        case 2:
          pPVar1->x = -pPVar1->x;
          iVar3 = pPVar1->y;
          break;
        case 3:
          iVar3 = pPVar1->x;
          pPVar1->x = pPVar1->y;
        }
        iVar3 = -iVar3;
LAB_00464440:
        pPVar1->y = iVar3;
      }
switchD_0046441a_caseD_0:
      pPVar1->x = pPVar1->x + position->x;
      count += -1;
      pPVar1->y = pPVar1->y + position->y;
      pPVar1 = pPVar1 + 1;
    } while (count != 0);
  }
  return Point2I_ARRAY_005023c8;
}