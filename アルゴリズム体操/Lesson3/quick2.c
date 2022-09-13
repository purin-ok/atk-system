/* ���ǔŃN�C�b�N�\�[�g �i�֐��̂݌f�ځj*/
void QuickSort(int bottom, int top, int *data)
{
  int lower, upper, div, temp;

  if (bottom>=top) return;

  div = data[(top+bottom)/2]; /* �z��̐^�񒆂��������l�ɂ��� */
  
  lower=bottom;  upper=top;
  while (1) {
    while (data[lower]<div) lower++;
    while (data[upper]>div) upper--;
    if (lower>=upper) break;
    /* �l�̌��� */
    temp = data[lower];  data[lower] = data[upper];  data[upper] = temp;
    lower++; upper--;
  }
  QuickSort(bottom, lower-1, data);
  QuickSort(upper+1, top, data);
}
