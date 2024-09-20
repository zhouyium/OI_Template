#pragma once

/*排序相关算法*/
//< 快速排序
//时间复杂度 O(nlogn)
//不稳定排序
void quick_sort(int q[], int l, int r) {
    if (l >= r) {
        return;
    }

    int i = l - 1, j = r + 1, x = q[l + r >> 1];
    while (i < j){
        do {
            i++;
        }while (q[i] < x);
        do {
            j --;
        }while (q[j] > x);
        if (i < j) {
            swap(q[i], q[j]);
        }
    }
    //分治
    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}

//< 归并排序
//时间复杂度 O(nlogn)
//稳定排序
void merge_sort(int q[], int l, int r){
    if (l >= r) {
        return;
    }

    int mid = l + r >> 1;
    merge_sort(q, l, mid);
    merge_sort(q, mid + 1, r);

    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r){
        if (q[i] <= q[j]) {
            tmp[k ++ ] = q[i ++ ];
        } else {
            tmp[k ++ ] = q[j ++ ];
        }
    }

    while (i <= mid) {
        tmp[k ++ ] = q[i ++ ];
    }
    while (j <= r) {
        tmp[k ++ ] = q[j ++ ];
    }

    for (i = l, j = 0; i <= r; i ++, j ++ ) {
        q[i] = tmp[j];
    }
}
