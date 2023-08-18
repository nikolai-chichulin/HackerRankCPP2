//
////
//const li n2 = 21;
//const li n3 = 14;
//const li n4 = 11;
//const li n56 = 9;
//const li n7 = 8;
//const li n89 = 7;
//
////
//li sum2[n2] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40 };
//li sum3[n3] = { 0,3,6,9,12,15,18,21,24,27,30,33,36,39 };
//li sum4[n4] = { 0,4,8,12,16,20,24,28,32,36,40 };
//li sum5[n56] = { 0,5,10,15,20,25,30,35,40 };
//li sum6[n56] = { 0,6,12,18,24,30,36,42,48 };
//li sum7[n7] = { 0,7,14,21,28,35,42,49 };
//li sum8[n89] = { 0,8,16,24,32,40,48 };
//li sum9[n89] = { 0,9,18,27,36,45,54 };
//
////
//li mult2[n2] = { 1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576 };
//li mult3[n3] = { 1,3,9,27,81,243,729,2187,6561,19683,59049,177147,531441,1594323 };
//li mult4[n4] = { 1,4,16,64,256,1024,4096,16384,65536,262144,1048576 };
//li mult5[n56] = { 1,5,25,125,625,3125,15625,78125,390625 };
//li mult6[n56] = { 1,6,36,216,1296,7776,46656,279936,1679616 };
//li mult7[n7] = { 1,7,49,343,2401,16807,117649,823543 };
//li mult8[n89] = { 1,8,64,512,4096,32768,262144 };
//li mult9[n89] = { 1,9,81,729,6561,59049,531441 };
//
//
///// <summary>
///// Returns the product-sum number for the given k.
///// </summary>
///// <param name="k">k is the number of terms/multipliers</param>
///// <returns></returns>
//li getres1(li k) {
//    li smax = 9l * li(k); // theoretical maximal sum
//    double smaxl = log10(smax);
//    li a2max = li(smaxl / log10(2)); // maximal count of 2-s
//    li ret = -1;
//    bool zerooverflow = false;
//    for (li a2 = 0; a2 <= a2max; a2++) { // the loop over the 2-s number
//        //outf2 << "->a2=" << a2 << endl;
//        // recalculate the theoretical maximum of the sum for a2 twos and k-a2 nines
//        smax = getsum(0, a2, 0, 0, 0, 0, 0, 0, k - a2);
//        smaxl = log10(smax);
//        li a3max = li(smaxl / log10(3)); // maximal count of 3-s
//        for (li a3 = 0; a3 <= a3max; a3++) { // the loop over the 3-s number
//            //outf2 << "-->a3=" << a3 << endl;
//            // recalculate the theoretical maximum of the sum for a2 twos, a3 threes, and k-a2 nines
//            smax = getsum(0, a2, a3, 0, 0, 0, 0, 0, k - a2 - a3);
//            smaxl = log10(smax);
//            li a4max = li(smaxl / log10(4)); // maximal count of 4-s
//            for (li a4 = 0; a4 <= a4max; a4++) { // the loop over the 4-s number
//                //outf2 << "--->a4=" << a4 << endl;
//                // recalculate the theoretical maximum of the sum...
//                smax = getsum(0, a2, a3, a4, 0, 0, 0, 0, k - a2 - a3 - a4);
//                smaxl = log10(smax);
//                li a5max = li(smaxl / log10(5));
//                for (li a5 = 0; a5 <= a5max; a5++) {
//                    //outf2 << "---->a5=" << a5 << endl;
//                    // recalculate the theoretical maximum of the sum...
//                    smax = getsum(0, a2, a3, a4, a5, 0, 0, 0, k - a2 - a3 - a4 - a5);
//                    smaxl = log10(smax);
//                    li a6max = li(smaxl / log10(6));
//                    for (li a6 = 0; a6 <= a6max; a6++) {
//                        //outf2 << "----->a6=" << a6 << endl;
//                        // recalculate the theoretical maximum of the sum...
//                        smax = getsum(0, a2, a3, a4, a5, a6, 0, 0, k - a2 - a3 - a4 - a5 - a6);
//                        smaxl = log10(smax);
//                        li a7max = li(smaxl / log10(7));
//                        for (li a7 = 0; a7 <= a7max; a7++) {
//                            //outf2 << "------>a7=" << a7 << endl;
//                            // recalculate the theoretical maximum of the sum...
//                            smax = getsum(0, a2, a3, a4, a5, a6, a7, 0, k - a2 - a3 - a4 - a5 - a6 - a7);
//                            smaxl = log10(smax);
//                            li a8max = li(smaxl / log10(8));
//                            for (li a8 = 0; a8 <= a8max; a8++) {
//                                //outf2 << "------->a8=" << a8 << endl;
//                                // recalculate the theoretical maximum of the sum...
//                                smax = getsum(0, a2, a3, a4, a5, a6, a7, a8, k - a2 - a3 - a4 - a5 - a6 - a7 - a8);
//                                smaxl = log10(smax);
//                                li a9max = li(smaxl / log10(9));
//                                for (li a9 = 0; a9 <= a9max; a9++) {
//                                    //outf2 << "-------->a9=" << a9 << endl;
//                                    li a1 = k - a2 - a3 - a4 - a5 - a6 - a7 - a8 - a9;
//                                    li sum = getsum(a1, a2, a3, a4, a5, a6, a7, a8, a9);
//                                    li mult = getmultN(a1, a2, a3, a4, a5, a6, a7, a8, a9);
//                                    if (mult > sum) {
//                                        zerooverflow = a9 == 0;
//                                        if (zerooverflow) {
//                                            //outf2 << " zero overflow a9, break " << endl;
//                                        }
//                                        else {
//                                            //outf2 << " overflow a9, break " << endl;
//                                        }
//                                        break;
//                                    }
//                                    if (sum == mult) {
//                                        outf1 << " found the number: " << sum << endl;
//                                        //outf2 << " found the number: " << sum << " a: " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 << ", " << a8 << ", " << a9 << endl;
//                                        if (ret == -1 || sum < ret) {
//                                            ret = sum;
//                                        }
//                                        break;
//                                    }
//                                }
//                                if (zerooverflow) {
//                                    zerooverflow = a8 == 0;
//                                    //if (zerooverflow) {
//                                    //    outf2 << " zero overflow a8, break " << endl;
//                                    //}
//                                    //else {
//                                    //    outf2 << " overflow a8, break " << endl;
//                                    //}
//                                    break;
//                                }
//                            }
//                            if (zerooverflow) {
//                                zerooverflow = a7 == 0;
//                                //if (zerooverflow) {
//                                //    outf2 << " zero overflow a7, break " << endl;
//                                //}
//                                //else {
//                                //    outf2 << " overflow a7, break " << endl;
//                                //}
//                                break;
//                            }
//                        }
//                        if (zerooverflow) {
//                            zerooverflow = a6 == 0;
//                            //if (zerooverflow) {
//                            //    outf2 << " zero overflow a6, break " << endl;
//                            //}
//                            //else {
//                            //    outf2 << " overflow a6, break " << endl;
//                            //}
//                            break;
//                        }
//                    }
//                    if (zerooverflow) {
//                        zerooverflow = a5 == 0;
//                        //if (zerooverflow) {
//                        //    outf2 << " zero overflow a5, break " << endl;
//                        //}
//                        //else {
//                        //    outf2 << " overflow a5, break " << endl;
//                        //}
//                        break;
//                    }
//                }
//                if (zerooverflow) {
//                    zerooverflow = a4 == 0;
//                    //if (zerooverflow) {
//                    //    outf2 << " zero overflow a4, break " << endl;
//                    //}
//                    //else {
//                    //    outf2 << " overflow a4, break " << endl;
//                    //}
//                    break;
//                }
//            }
//            if (zerooverflow) {
//                zerooverflow = a3 == 0;
//                //if (zerooverflow) {
//                //    outf2 << " zero overflow a3, break " << endl;
//                //}
//                //else {
//                //    outf2 << " overflow a3, break " << endl;
//                //}
//                break;
//            }
//        }
//        if (zerooverflow) {
//            zerooverflow = a2 == 0;
//            //if (zerooverflow) {
//            //    outf2 << " zero overflow a2, break " << endl;
//            //}
//            //else {
//            //    outf2 << " overflow a2, break " << endl;
//            //}
//            break;
//        }
//    }
//    if (ret != -1) {
//        outf1 << "  ---> the final sum is: " << ret << endl;
//    }
//    return ret;
//}
//
///// <summary>
///// Returns the product-sum number for the given k.
///// </summary>
///// <param name="k">k is the number of terms/multipliers</param>
///// <returns></returns>
//li getres2(li k) {
//    li ret = -1;
//    bool zerooverflow = false;
//    for (li a2 = 0; a2 < n2; a2++) { // the loop over the 2-s number
//        //outf2 << "->a2=" << a2 << endl;
//        li a1 = k - a2;
//        for (li a3 = 0; a3 < n3; a3++) { // the loop over the 3-s number
//            //outf2 << "-->a3=" << a3 << endl;
//            for (li a4 = 0; a4 < n4; a4++) { // the loop over the 4-s number
//                //outf2 << "--->a4=" << a4 << endl;
//                for (li a5 = 0; a5 < n56; a5++) {
//                    //outf2 << "---->a5=" << a5 << endl;
//                    for (li a6 = 0; a6 < n56; a6++) {
//                        //outf2 << "----->a6=" << a6 << endl;
//                        for (li a7 = 0; a7 < n7; a7++) {
//                            //outf2 << "------>a7=" << a7 << endl;
//                            for (li a8 = 0; a8 < n89; a8++) {
//                                //outf2 << "------->a8=" << a8 << endl;
//                                for (li a9 = 0; a9 < n89; a9++) {
//                                    //outf2 << "-------->a9=" << a9 << endl;
//                                    li a1 = k - a2 - a3 - a4 - a5 - a6 - a7 - a8 - a9;
//                                    li sum = a1 + sum2[a2] + sum3[a3] + sum4[a4] + sum5[a5] + sum6[a6] + sum7[a7] + sum8[a8] + sum9[a9];
//                                    //li sum = getsum(a1, a2, a3, a4, a5, a6, a7, a8, a9);
//                                    li mult = getmult(a1, a2, a3, a4, a5, a6, a7, a8, a9);
//                                    if (mult > sum) {
//                                        zerooverflow = a9 == 0;
//                                        if (zerooverflow) {
//                                            //outf2 << " zero overflow a9, break " << endl;
//                                        }
//                                        else {
//                                            //outf2 << " overflow a9, break " << endl;
//                                        }
//                                        break;
//                                    }
//                                    if (sum == mult) {
//                                        outf1 << " found the number: " << sum << endl;
//                                        //outf2 << " found the number: " << sum << " a: " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 << ", " << a8 << ", " << a9 << endl;
//                                        if (ret == -1 || sum < ret) {
//                                            ret = sum;
//                                        }
//                                        break;
//                                    }
//                                }
//                                if (zerooverflow) {
//                                    zerooverflow = a8 == 0;
//                                    //if (zerooverflow) {
//                                    //    outf2 << " zero overflow a8, break " << endl;
//                                    //}
//                                    //else {
//                                    //    outf2 << " overflow a8, break " << endl;
//                                    //}
//                                    break;
//                                }
//                            }
//                            if (zerooverflow) {
//                                zerooverflow = a7 == 0;
//                                //if (zerooverflow) {
//                                //    outf2 << " zero overflow a7, break " << endl;
//                                //}
//                                //else {
//                                //    outf2 << " overflow a7, break " << endl;
//                                //}
//                                break;
//                            }
//                        }
//                        if (zerooverflow) {
//                            zerooverflow = a6 == 0;
//                            //if (zerooverflow) {
//                            //    outf2 << " zero overflow a6, break " << endl;
//                            //}
//                            //else {
//                            //    outf2 << " overflow a6, break " << endl;
//                            //}
//                            break;
//                        }
//                    }
//                    if (zerooverflow) {
//                        zerooverflow = a5 == 0;
//                        //if (zerooverflow) {
//                        //    outf2 << " zero overflow a5, break " << endl;
//                        //}
//                        //else {
//                        //    outf2 << " overflow a5, break " << endl;
//                        //}
//                        break;
//                    }
//                }
//                if (zerooverflow) {
//                    zerooverflow = a4 == 0;
//                    //if (zerooverflow) {
//                    //    outf2 << " zero overflow a4, break " << endl;
//                    //}
//                    //else {
//                    //    outf2 << " overflow a4, break " << endl;
//                    //}
//                    break;
//                }
//            }
//            if (zerooverflow) {
//                zerooverflow = a3 == 0;
//                //if (zerooverflow) {
//                //    outf2 << " zero overflow a3, break " << endl;
//                //}
//                //else {
//                //    outf2 << " overflow a3, break " << endl;
//                //}
//                break;
//            }
//        }
//        if (zerooverflow) {
//            zerooverflow = a2 == 0;
//            //if (zerooverflow) {
//            //    outf2 << " zero overflow a2, break " << endl;
//            //}
//            //else {
//            //    outf2 << " overflow a2, break " << endl;
//            //}
//            break;
//        }
//    }
//    if (ret != -1) {
//        outf1 << "  ---> the final sum is: " << ret << endl;
//    }
//    return ret;
//}
//
//li prerun() {
//    const li maxnum = 12000;
//    li res1[maxnum + 1] = {};
//    li res2[2 * maxnum] = {};
//    li k = 0;
//    li i = 0;
//    for (li a2 = 0; a2 < n2; a2++) {
//        li sm2 = sum2[a2];
//        li mlt2 = mult2[a2];
//        if (mlt2 > maxnum) {
//            break;
//        }
//        for (li a3 = 0; a3 < n3; a3++) {
//            li sm3 = sm2 + sum3[a3];
//            li mlt3 = mlt2 * mult3[a3];
//            if (mlt3 > maxnum) {
//                break;
//            }
//            for (li a4 = 0; a4 < n4; a4++) {
//                li sm4 = sm3 + sum4[a4];
//                li mlt4 = mlt3 * mult4[a4];
//                if (mlt4 > maxnum) {
//                    break;
//                }
//                for (li a5 = 0; a5 < n56; a5++) {
//                    li sm5 = sm4 + sum5[a5];
//                    li mlt5 = mlt4 * mult5[a5];
//                    if (mlt5 > maxnum) {
//                        break;
//                    }
//                    for (li a6 = 0; a6 < n56; a6++) {
//                        li sm6 = sm5 + sum6[a6];
//                        li mlt6 = mlt5 * mult6[a6];
//                        if (mlt6 > maxnum) {
//                            break;
//                        }
//                        for (li a7 = 0; a7 < n7; a7++) {
//                            li sm7 = sm6 + sum7[a7];
//                            li mlt7 = mlt6 * mult7[a7];
//                            if (mlt7 > maxnum) {
//                                break;
//                            }
//                            for (li a8 = 0; a8 < n89; a8++) {
//                                li sm8 = sm7 + sum8[a8];
//                                li mlt8 = mlt7 * mult8[a8];
//                                if (mlt8 > maxnum) {
//                                    break;
//                                }
//                                for (li a9 = 0; a9 < n89; a9++) {
//                                    i++;
//                                    li sm9 = sm8 + sum9[a9];
//                                    sums[a2][a3][a4][a5][a6][a7][a8][a9] = sm9;
//                                    li mlt9 = mlt8 * mult9[a9];
//                                    if (mlt9 > maxnum) {
//                                        break;
//                                    }
//                                    mult[a2][a3][a4][a5][a6][a7][a8][a9] = mlt9;
//                                    li n = a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9;
//                                    li a1 = mlt9 - sm9;
//                                    k = a1 + n;
//                                    if (k > 1 && k <= maxnum) {
//                                        outf2 << "k = " << k << " mult = " << mlt9 << " a: " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 << ", " << a8 << ", " << a9 << endl;
//                                        if (res1[k] == 0 || res1[k] > mlt9) {
//                                            res1[k] = mlt9;
//                                        }
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//    outf2 << "-------------------- direct output --------------------" << endl;
//    for (li i = 2; i <= maxnum; i++) {
//        outf2 << "k = " << i << " mult = " << res1[i] << endl;
//    }
//    outf2 << "-------------------- reverse output --------------------" << endl;
//    li res = 0;
//    for (li i = 2; i <= maxnum; i++) {
//        if (res2[res1[i]] == 0) {
//            res2[res1[i]] = i;
//        }
//    }
//    for (li i = 0; i < 2 * maxnum; i++) {
//        if (i > 0 && res2[i] > 1 && res2[i] <= maxnum) {
//            outf2 << " k = " << res2[i] << " mult = " << i << endl;
//        }
//    }
//
//    return i;
//}
//
///// <summary>
///// Returns the product-sum number for the given k.
///// </summary>
///// <param name="k">k is the number of terms/multipliers</param>
///// <returns></returns>
//li getres3(li k) {
//    li ret = -1;
//    bool zerooverflow = false;
//    for (li a2 = 0; a2 < n2; a2++) { // the loop over the 2-s number
//        //outf2 << "->a2=" << a2 << endl;
//        for (li a3 = 0; a3 < n3; a3++) { // the loop over the 3-s number
//            //outf2 << "-->a3=" << a3 << endl;
//            for (li a4 = 0; a4 < n4; a4++) { // the loop over the 4-s number
//                //outf2 << "--->a4=" << a4 << endl;
//                for (li a5 = 0; a5 < n56; a5++) {
//                    //outf2 << "---->a5=" << a5 << endl;
//                    for (li a6 = 0; a6 < n56; a6++) {
//                        //outf2 << "----->a6=" << a6 << endl;
//                        for (li a7 = 0; a7 < n7; a7++) {
//                            //outf2 << "------>a7=" << a7 << endl;
//                            for (li a8 = 0; a8 < n89; a8++) {
//                                //outf2 << "------->a8=" << a8 << endl;
//                                for (li a9 = 0; a9 < n89; a9++) {
//                                    //outf2 << "-------->a9=" << a9 << endl;
//                                    li a1 = k - a2 - a3 - a4 - a5 - a6 - a7 - a8 - a9;
//                                    li sum = sums[a2][a3][a4][a5][a6][a7][a8][a9] + a1;
//                                    li mlt = mult[a2][a3][a4][a5][a6][a7][a8][a9];
//                                    if (mlt > sum) {
//                                        zerooverflow = a9 == 0;
//                                        if (zerooverflow) {
//                                            //outf2 << " zero overflow a9, break " << endl;
//                                        }
//                                        else {
//                                            //outf2 << " overflow a9, break " << endl;
//                                        }
//                                        break;
//                                    }
//                                    if (sum == mlt) {
//                                        outf1 << " found the number: " << sum << endl;
//                                        //outf2 << " found the number: " << sum << " a: " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 << ", " << a8 << ", " << a9 << endl;
//                                        if (ret == -1 || sum < ret) {
//                                            ret = sum;
//                                        }
//                                        break;
//                                    }
//                                }
//                                if (zerooverflow) {
//                                    zerooverflow = a8 == 0;
//                                    //if (zerooverflow) {
//                                    //    outf2 << " zero overflow a8, break " << endl;
//                                    //}
//                                    //else {
//                                    //    outf2 << " overflow a8, break " << endl;
//                                    //}
//                                    break;
//                                }
//                            }
//                            if (zerooverflow) {
//                                zerooverflow = a7 == 0;
//                                //if (zerooverflow) {
//                                //    outf2 << " zero overflow a7, break " << endl;
//                                //}
//                                //else {
//                                //    outf2 << " overflow a7, break " << endl;
//                                //}
//                                break;
//                            }
//                        }
//                        if (zerooverflow) {
//                            zerooverflow = a6 == 0;
//                            //if (zerooverflow) {
//                            //    outf2 << " zero overflow a6, break " << endl;
//                            //}
//                            //else {
//                            //    outf2 << " overflow a6, break " << endl;
//                            //}
//                            break;
//                        }
//                    }
//                    if (zerooverflow) {
//                        zerooverflow = a5 == 0;
//                        //if (zerooverflow) {
//                        //    outf2 << " zero overflow a5, break " << endl;
//                        //}
//                        //else {
//                        //    outf2 << " overflow a5, break " << endl;
//                        //}
//                        break;
//                    }
//                }
//                if (zerooverflow) {
//                    zerooverflow = a4 == 0;
//                    //if (zerooverflow) {
//                    //    outf2 << " zero overflow a4, break " << endl;
//                    //}
//                    //else {
//                    //    outf2 << " overflow a4, break " << endl;
//                    //}
//                    break;
//                }
//            }
//            if (zerooverflow) {
//                zerooverflow = a3 == 0;
//                //if (zerooverflow) {
//                //    outf2 << " zero overflow a3, break " << endl;
//                //}
//                //else {
//                //    outf2 << " overflow a3, break " << endl;
//                //}
//                break;
//            }
//        }
//        if (zerooverflow) {
//            zerooverflow = a2 == 0;
//            //if (zerooverflow) {
//            //    outf2 << " zero overflow a2, break " << endl;
//            //}
//            //else {
//            //    outf2 << " overflow a2, break " << endl;
//            //}
//            break;
//        }
//    }
//    if (ret != -1) {
//        outf1 << "  ---> the final sum is: " << ret << endl;
//    }
//    return ret;
//}
//
///// <summary>
///// Returns the product-sum number for the given k.
///// </summary>
///// <param name="k">k is the number of terms/multipliers</param>
///// <returns></returns>
//li getresBF(li k) {
//    li ret = -1;
//    for (li a2 = 0; a2 <= k; a2++) { // the loop over the 2-s number
//        //cout << "->a2=" << a2 << endl;
//        //outf2 << "->a2=" << a2 << endl;
//        for (li a3 = 0; a3 <= k - a2; a3++) { // the loop over the 3-s number
//            //cout << "-->a3=" << a3 << endl;
//            //outf2 << "-->a3=" << a3 << endl;
//            for (li a4 = 0; a4 <= k - a2 - a3; a4++) { // the loop over the 4-s number
//                //cout << "--->a4=" << a4 << endl;
//                //outf2 << "--->a4=" << a4 << endl;
//                for (li a5 = 0; a5 <= k - a2 - a3 - a4; a5++) {
//                    //cout << "---->a5=" << a5 << endl;
//                    //outf2 << "---->a5=" << a5 << endl;
//                    for (li a6 = 0; a6 <= k - a2 - a3 - a4 - a5; a6++) {
//                        //outf2 << "----->a6=" << a6 << endl;
//                        for (li a7 = 0; a7 <= k - a2 - a3 - a4 - a5 - a6; a7++) {
//                            //outf2 << "------>a7=" << a7 << endl;
//                            for (li a8 = 0; a8 <= k - a2 - a3 - a4 - a5 - a6 - a7; a8++) {
//                                //outf2 << "------->a8=" << a8 << endl;
//                                for (li a9 = 0; a9 <= k - a2 - a3 - a4 - a5 - a6 - a7 - a8; a9++) {
//                                    //outf2 << "-------->a9=" << a9 << endl;
//                                    li a1 = k - a2 - a3 - a4 - a5 - a6 - a7 - a8 - a9;
//                                    li sum = getsum(a1, a2, a3, a4, a5, a6, a7, a8, a9);
//                                    li mult = getmult(a1, a2, a3, a4, a5, a6, a7, a8, a9);
//                                    if (mult == 48) {
//                                        cout << " found 48: " << sum << " a: " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 << ", " << a8 << ", " << a9 << endl;
//                                    }
//                                    if (sum == mult) {
//                                        outf1 << " found the number: " << sum << endl;
//                                        outf2 << " found the number: " << sum << " a: " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 << ", " << a8 << ", " << a9 << endl;
//                                        if (ret == -1 || sum < ret) {
//                                            ret = sum;
//                                        }
//                                        break;
//                                    }
//                                    if (mult > sum) {
//                                        break;
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//    if (ret != -1) {
//        outf1 << "  ---> the final sum is: " << ret << endl;
//    }
//    return ret;
//}
