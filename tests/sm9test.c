/*
 * Copyright (c) 2016 - 2021 The GmSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the GmSSL Project.
 *    (http://gmssl.org/)"
 *
 * 4. The name "GmSSL Project" must not be used to endorse or promote
 *    products derived from this software without prior written
 *    permission. For written permission, please contact
 *    guanzhi1980@gmail.com.
 *
 * 5. Products derived from this software may not be called "GmSSL"
 *    nor may "GmSSL" appear in their names without prior written
 *    permission of the GmSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the GmSSL Project
 *    (http://gmssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE GmSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE GmSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmssl/sm9.h>
#include <gmssl/error.h>
#include <gmssl/rand.h>


#define hex_iv 		"123456789abcdef00fedcba987654321123456789abcdef00fedcba987654321"
#define hex_fp_add 	"114efe24536598809df494ff7657484edff1812d51c3955b7d869149aa123d31"
#define hex_fp_sub 	"43cee97c9abed9be3efe7ffffc9d30abe1d643b9b27ea351460aabb2239d3fd4"
#define hex_fp_nsub 	"7271168367e4cd3397052b4ff8f19699401c4f9167fc4b8a9f64ef75bfb405a9"
#define hex_fp_dbl 	"551de7a0ee24723edcf314ff72f478fac1c7c4e7044238acc3913cfbcdaf7d05"
#define hex_fp_tri 	"248cdb7163e4d7e5606ac9d731a751d591b25db4f925dd9532a20de5c2de98c9"
#define hex_fp_div2 	"9df779e83d83d9c517bf85bbd4e833b289e7dfb214ecc1501cf8039cdde8d35f"
#define hex_fp_neg 	"30910c2f8a3f9a597c884b28414d2725301567320b1c5b1790ef2f160ad0e43c"
#define hex_fp_mul 	"9e4d19bb5d94a47352e6f53f4116b2a71b16a1113dc789b26528ee19f46b72e0"
#define hex_fp_sqr 	"46dc2a5b8853234b341d9c57f9c4ca5709e95bbfef25356812e884e4f38cd0d6"
#define hex_fp_pow 	"5679a8f0a46ada5b9d48008cde0b8b7a233f882c08afe8f08a36a20ac845bb1a"
#define hex_fp_inv 	"7d404b0027a93e3fa8f8bc7ee367a96814c42a3b69feb1845093406948a34753"

int test_sm9_fp() {
	sm9_fp_t x;
	sm9_fp_t y;
	sm9_fp_t r;
	int j = 1;
	
	sm9_bn_copy(x, SM9_P2->X[1]);
	sm9_bn_copy(y, SM9_Ppubs->Y[0]);
	
	sm9_fp_t iv = {0x87654321, 0x0fedcba9, 0x9abcdef0, 0x12345678, 0x87654321, 0x0fedcba9, 0x9abcdef0, 0x12345678};
	sm9_bn_from_hex(r, hex_iv); if (sm9_bn_cmp(r, iv) != 0) goto err; ++j;
	
	sm9_fp_add(r, x, y); if (!sm9_bn_equ_hex(r, hex_fp_add)) goto err; ++j;
	sm9_fp_sub(r, x, y); if (!sm9_bn_equ_hex(r, hex_fp_sub)) goto err; ++j;
	sm9_fp_sub(r, y, x); if (!sm9_bn_equ_hex(r, hex_fp_nsub)) goto err; ++j;
	sm9_fp_dbl(r, x);    if (!sm9_bn_equ_hex(r, hex_fp_dbl)) goto err; ++j;
	sm9_fp_tri(r, x);    if (!sm9_bn_equ_hex(r, hex_fp_tri)) goto err; ++j;
	sm9_fp_div2(r, x);   if (!sm9_bn_equ_hex(r, hex_fp_div2)) goto err; ++j;
	sm9_fp_neg(r, x);    if (!sm9_bn_equ_hex(r, hex_fp_neg)) goto err; ++j;
	sm9_fp_mul(r, x, y); if (!sm9_bn_equ_hex(r, hex_fp_mul)) goto err; ++j;
	sm9_fp_sqr(r, x);    if (!sm9_bn_equ_hex(r, hex_fp_sqr)) goto err; ++j;
	sm9_fp_pow(r, x, y); if (!sm9_bn_equ_hex(r, hex_fp_pow)) goto err; ++j;
	sm9_fp_inv(r, x);    if (!sm9_bn_equ_hex(r, hex_fp_inv)) goto err; ++j;
	
	printf("%s() ok\n", __FUNCTION__);
	return 1;
err:
	printf("%s test %d failed\n", __FUNCTION__, j);
	error_print();
	return -1;
}

#define hex_iv2 	"123456789abcdef00fedcba987654321123456789abcdef00fedcba987654321-a39654024e243d806e492768664a2b72d632457dd14f49a9f1fdd299c9bb073c"
#define hex_fp2_add	"0074a3145c65ac547541612178e584a902248740e70606dcaaafe2bcbd2f6a21-1b6ac9eb2c47b62cf61608b26c3c7e20674a48c4c509ac130bbaf6d47d32c07c"
#define hex_fp2_dbl	"2ea136125d08b824cd741a4c597dcdda0e6d52df468f917b0adb8ed709d7d72c-995e51aa30d8d45ae85f34da84c0589f6dece1e633b92146debbdc23afe20a11"
#define hex_fp2_tri	"45f1d11b8b8d1437342e2772863cb4c715a3fc4ee9d75a38904956428ec3c2c2-8aed7a7f47f36b0f718cf99fcc59214c93ea0933c0583a7c5b61fca1962a6c5b"
#define hex_fp2_sub	"2e2c92fe00a30bd05832b92ae09849310c48cb9e5f898a9e602bac1a4ca86d0b-7df387bf04911e2df2492c281883da7f06a299216eaf7533d300e54f32af4995"
#define hex_fp2_neg	"9eef64f6d41f4adf6f499e29c8cfe0581abbe9db7733261e6001d3bc5e6559e7-0e70d72ae8e5694b76d23b3ab8673752da02d8b27360e6ca8359df8219b79db6"
#define hex_fp2_mul	"192eb5c3350a03e4baf23dd035b8804af8d5189c710adda53edd9cc0633f2d67-27fe3a559abcc3e1b1fc3f1eb35b4bd5e465f0ef2bcb9997b36e3548637456b6"
#define hex_fp2_mul_u	"27fe3a559abcc3e1b1fc3f1eb35b4bd5e465f0ef2bcb9997b36e3548637456b6-83e29479988f9f28601f2faf8a1dc6af304862123865339167b461a71cd2eaaf"
#define hex_fp2_mul_fp	"546e5945201b73c6ae44053114761efe351d5884c737301cfc7d2376d349a616-3c2f6327ef1c5aa1d06e8cebc4100f0758c04476f40e8a0facb0a0bf09a9dd42"
#define hex_fp2_sqr	"8896d4306fb19d0e4a0e09899240e35cafed70bebb3ad56cf7b07964fefdfb93-16bd622a907d7a92e475ed336e8ebca2cc1e38dd2ae69aaf2a96208eba0ee06e"
#define hex_fp2_sqr_u	"16bd622a907d7a92e475ed336e8ebca2cc1e38dd2ae69aaf2a96208eba0ee06e-5b52579f25e413c717eb438cc69bc7d0e40a4518be8032dddb7e4385c8a693d4"
#define hex_fp2_inv	"93ceda7dddd537eb9307a06313598e650a568d931d16ab98ca0a7483c3b502e2-6face8b958e2bdc0771fd9d700f2703f881ef0d13509f16937f0a0c344647175"
#define hex_fp2_div	"ad68ff7c507f2d4e1cc6cd973c6b821906b9f5937a04fdedc84af1f75f97d00b-8a84a35da11d401c8dca50a572ce7a8c99e7117c45d251f57a2418613dab16bb"
#define hex_fp2_div2	"0ba84d8497422e09335d0693165f7376839b54b7d1a3e45ec2b6e3b5c275f5cb-af07946a8e30f24c1a9a8db2995b2b9bb4f126f1e0ca7b76a3c2ab66d67576a2"

int test_sm9_fp2() {
	sm9_fp2_t x;
	sm9_fp2_t y;
	sm9_fp2_t r;
	sm9_fp2_t s;
	sm9_fp_t k;
	int j = 1;
	
	sm9_fp2_copy(x, SM9_P2->Y);
	sm9_fp2_copy(y, SM9_Ppubs->X);
	sm9_bn_from_hex(k, hex_iv);
	
	sm9_fp2_t iv2 = {{0xc9bb073c, 0xf1fdd299, 0xd14f49a9, 0xd632457d, 0x664a2b72, 0x6e492768, 0x4e243d80, 0xa3965402},
	                 {0x87654321, 0x0fedcba9, 0x9abcdef0, 0x12345678, 0x87654321, 0x0fedcba9, 0x9abcdef0, 0x12345678}};
	sm9_fp2_from_hex(r, hex_iv2); if (!sm9_fp2_equ(r, iv2)) goto err; ++j;
	
	sm9_fp2_add(r, x, y);    sm9_fp2_from_hex(s, hex_fp2_add); if (!sm9_fp2_equ(r, s)) goto err; ++j;
	sm9_fp2_dbl(r, x);       sm9_fp2_from_hex(s, hex_fp2_dbl); if (!sm9_fp2_equ(r, s)) goto err; ++j;
	sm9_fp2_tri(r, x);       sm9_fp2_from_hex(s, hex_fp2_tri); if (!sm9_fp2_equ(r, s)) goto err; ++j;
	sm9_fp2_sub(r, x, y);    sm9_fp2_from_hex(s, hex_fp2_sub); if (!sm9_fp2_equ(r, s)) goto err; ++j;
	sm9_fp2_neg(r, x);       sm9_fp2_from_hex(s, hex_fp2_neg); if (!sm9_fp2_equ(r, s)) goto err; ++j;
	sm9_fp2_mul(r, x, y);    sm9_fp2_from_hex(s, hex_fp2_mul); if (!sm9_fp2_equ(r, s)) goto err; ++j;
	sm9_fp2_mul_u(r, x, y);  sm9_fp2_from_hex(s, hex_fp2_mul_u); if (!sm9_fp2_equ(r, s)) goto err; ++j;
	sm9_fp2_mul_fp(r, x, k); sm9_fp2_from_hex(s, hex_fp2_mul_fp); if (!sm9_fp2_equ(r, s)) goto err; ++j;
	sm9_fp2_sqr(r, x);       sm9_fp2_from_hex(s, hex_fp2_sqr); if (!sm9_fp2_equ(r, s)) goto err; ++j;
	sm9_fp2_sqr_u(r, x);     sm9_fp2_from_hex(s, hex_fp2_sqr_u); if (!sm9_fp2_equ(r, s)) goto err; ++j;
	sm9_fp2_inv(r, x);       sm9_fp2_from_hex(s, hex_fp2_inv); if (!sm9_fp2_equ(r, s)) goto err; ++j;
	sm9_fp2_div(r, x, y);    sm9_fp2_from_hex(s, hex_fp2_div); if (!sm9_fp2_equ(r, s)) goto err; ++j;
	sm9_fp2_div2(r, x);      sm9_fp2_from_hex(s, hex_fp2_div2); if (!sm9_fp2_equ(r, s)) goto err; ++j;
	
	printf("%s() ok\n", __FUNCTION__);
	return 1;
err:
	printf("%s test %d failed\n", __FUNCTION__, j);
	error_print();
	return -1;
}

#define hex_iv4 	"123456789abcdef00fedcba987654321123456789abcdef00fedcba987654321\
-a39654024e243d806e492768664a2b72d632457dd14f49a9f1fdd299c9bb073c\
-123456789abcdef00fedcba987654321123456789abcdef00fedcba987654321\
-a39654024e243d806e492768664a2b72d632457dd14f49a9f1fdd299c9bb073c"
#define hex_fp4_mul	"11d8f3dc2c4a7cd3ff4d557d86871210cff65187190711430b2d898affd61cda\
-960ee85c0aaacd6cc805053293a4955245ba973c9972b6767d0c68450a905ee7\
-ac9891b21d82827f6ccc2cd8524179b833239019c0b66cad89d7d8735ee03782\
-8f456b1cee442d189d01fc42fff7fd8481173dae8dc547d85c01a843005a063e"
#define hex_fp4_mul_fp	"413b76fe8748ab9130dc2907a55c15da925b496395c2cd82d6311863a4d9cfa8\
-5cc754d5318f3ed489db7e53f94f3878a527053693983f4d4a61b30f6ea74984\
-6769891769934201aa8d6de63cc012ec2b722d7b0ad9c9039246a3eea6f3d479\
-408d33e58a4d3bfaf1d84a7ddad4e4026ca41f2aaa179611d9894584baed89d0"
#define hex_fp4_mul_fp2	"242956015bdff53db568b970d64a7de56a0506309e1309b283317134dd52d53e\
-5333c472d44677df131eeb1180badb3e1e9f88ba58190d16a92d95f939efb2c3\
-0ccdaa76a6876ff69de6792161b614ca720bfcee2d5521533fbb28179ec0e31e\
-2a2d6b832e919c313920f2e13e822795e2ceda8c0d8f4abe78220e4e00aeb6fd"
#define hex_fp4_mul_v	"ac9891b21d82827f6ccc2cd8524179b833239019c0b66cad89d7d8735ee03782\
-8f456b1cee442d189d01fc42fff7fd8481173dae8dc547d85c01a843005a063e\
-960ee85c0aaacd6cc805053293a4955245ba973c9972b6767d0c68450a905ee7\
-928e1847aa0ead49d7690054e880a3238205f03ce86ccc55cf148811e3a50bc9"
#define hex_fp4_sqr	"8d3bc7848d4ad61017a7cb4efc280103bfe558e240c46c5765f1a4e2ec2e8c54\
-2f0f2ef9dd3979c7018b67837ba6e73938ba88ae66a101aaa0cf27ee449835ec\
-93838cbf9e5be34562c5bc031e27357d206f783837a6a921cbf4829292b69441\
-3681ecc58b68ffc15af31c5b1f1e10e1f3c60bdabb329c0dc7ffb2cc3925f005"
#define hex_fp4_sqr_v	"93838cbf9e5be34562c5bc031e27357d206f783837a6a921cbf4829292b69441\
-3681ecc58b68ffc15af31c5b1f1e10e1f3c60bdabb329c0dc7ffb2cc3925f005\
-2f0f2ef9dd3979c7018b67837ba6e73938ba88ae66a101aaa0cf27ee449835ec\
-520870f6eab1a1c37cb7c001f2cd8c82c41a74d1b36d0508fefbec89ee457252"
#define hex_fp4_inv	"1ec69309f84c5ad450750826fc804b72fb89fb48474222ba05be08bb1765f1d6\
-3f16de331f77f510a3ec06e79319e3be5b3777471f79cd53404652b485133e99\
-1cbf7f3bb04e2389184eade12de2752711cbff452363d2dfaf2bfef40618cebc\
-3a70e829b83dc311970bc8d3e3e652f88a1ecd49b4672aa18c1c613c9a97d86f"

int test_sm9_fp4() {
	sm9_fp4_t x;
	sm9_fp4_t y;
	sm9_fp4_t r;
	sm9_fp4_t s;
	sm9_fp2_t q;
	sm9_fp_t k;
	int j = 1;
	
	sm9_fp2_from_hex(x[0], hex_fp2_mul_fp);
	sm9_fp2_from_hex(x[1], hex_fp2_sqr);
	sm9_fp2_from_hex(y[0], hex_fp2_add);
	sm9_fp2_from_hex(y[1], hex_fp2_tri);
	sm9_bn_from_hex(k, hex_iv);
	sm9_fp2_copy(q, SM9_Ppubs->X);
	
	sm9_fp4_t iv4 = {{{0xc9bb073c, 0xf1fdd299, 0xd14f49a9, 0xd632457d, 0x664a2b72, 0x6e492768, 0x4e243d80, 0xa3965402},
	                  {0x87654321, 0x0fedcba9, 0x9abcdef0, 0x12345678, 0x87654321, 0x0fedcba9, 0x9abcdef0, 0x12345678}},
			 {{0xc9bb073c, 0xf1fdd299, 0xd14f49a9, 0xd632457d, 0x664a2b72, 0x6e492768, 0x4e243d80, 0xa3965402},
	                  {0x87654321, 0x0fedcba9, 0x9abcdef0, 0x12345678, 0x87654321, 0x0fedcba9, 0x9abcdef0, 0x12345678}}};
	sm9_fp4_from_hex(r, hex_iv4); if (!sm9_fp4_equ(r, iv4)) goto err; ++j;
	
	sm9_fp4_mul(r, x, y);        sm9_fp4_from_hex(s, hex_fp4_mul); if (!sm9_fp4_equ(r, s)) goto err; ++j;
	sm9_fp4_mul_fp(r, x, k);     sm9_fp4_from_hex(s, hex_fp4_mul_fp); if (!sm9_fp4_equ(r, s)) goto err; ++j;
	sm9_fp4_mul_fp2(r, x, q);    sm9_fp4_from_hex(s, hex_fp4_mul_fp2); if (!sm9_fp4_equ(r, s)) goto err; ++j;
	sm9_fp4_mul_v(r, x, y);      sm9_fp4_from_hex(s, hex_fp4_mul_v); if (!sm9_fp4_equ(r, s)) goto err; ++j;
	sm9_fp4_sqr(r, x);           sm9_fp4_from_hex(s, hex_fp4_sqr); if (!sm9_fp4_equ(r, s)) goto err; ++j;
	sm9_fp4_sqr_v(r, x);         sm9_fp4_from_hex(s, hex_fp4_sqr_v); if (!sm9_fp4_equ(r, s)) goto err; ++j;
	sm9_fp4_inv(r, x);           sm9_fp4_from_hex(s, hex_fp4_inv); if (!sm9_fp4_equ(r, s)) goto err; ++j;
	
	printf("%s() ok\n", __FUNCTION__);
	return 1;
err:
	printf("%s test %d failed\n", __FUNCTION__, j);
	error_print();
	return -1;
}

#define hex_fp12_mul	"058d43459faee14ba2b6a69ff2d8c3ad933a1253e1764dedf5419b144a2ab82b\
-20ef84805ba02ef92a48fb2ae8086e566a644ab0639249f175268f18d8091ad4\
-83cc3be54a699ae24d8f920c87baa395befb424a6dcad1dcdfc2a006765ef8d5\
-1d705169165d9c2386c3bc673df3fa84975afa955a7be27f1b362000a96b8c2c\
-22b910d826f02961ff0fed439beb1e91f45193f87c2cdd9562da539290846ace\
-2c618991ae82d35063cfed629ff7d930b8070ba07d0652ba092f046e133e3491\
-137bc78a9aa182330bd71fb8859314422dd36f5e3c1f6fd36d6c9685fc39419f\
-8d83e7380abe10a2f3677864c2dbbcdad7ae5434e92043a2da3b71f3f9cedd8c\
-850c0562ac08996c05d22ea466cf4b1fa7a7064d4653b5fa725d623254bf7125\
-6dc41016b3ab9b44a4841aa8037e3b4d331cc7c8313abee0c5111a9be5915e90\
-6d1a15e5b765c4b139bf5c6c4a87214c269b26fb709ff5de885c053f405cf626\
-8d4d853489a4a5d809fa77e35627a5351651b926f001e1ee46e95808f9001d24"
#define hex_fp12_sqr	"3592cba3482fb39756b2ed1d3d756685caa005bd5e8288bc92841d29276aa321\
-8e3a49919e6de83b1ab1a5bb9eb993c3bbd68e8d305aed5c0b88cef0ef41c47f\
-3d3d9cc8e07619efd21745f6938a26f7cb0a83ad4aa3a9d066e18ad99833e3ac\
-25195ec7af551c42d7d37a0b120607d4adba6b9377299688b92a8393f3b8c20f\
-76f676d5d2cb8d1a2cc237fc78c8d544bef1cd560e654236f502aed0d8c9148c\
-6cde174a5e9d117175a4a163f041b65f868dffa05b5f3474f729b87f92493f2c\
-667a86d73e8f88a81306f7f0cd28789a55bf7e9cbe155fc6abb300ad027d8801\
-a49a66d48ec2ef72a9929413a40e316a8aee1d6236a1db8c56496524f1c23f11\
-1684bc9679aaba4afe35ec8c0852e438f41e15ab37620d9661018f90fe7415f1\
-8d37fb8b7edf942885b3009cf7e295bea89444d34091fc57380c778395b7c4e4\
-278b9d9ea61b6b2758e758ed9a64034576b520e65a9d276a0c82f079501a226e\
-01a333fa4177601de7cd8ed49ea4906f30e23988dcb7cde173da48499fce3ee5"
#define hex_fp12_inv	"47ae900b90945e31afde7fe09f0b69640c468a1648ee52070584a5d13af22bb9\
-8f273655182c3a9f184dc30421161ecdd50655c36a9266c7df1016e410f34102\
-a26e789013203804b5f8f1c5a51dd3fb50176d41108b235d6e66712721060252\
-090aaed5cb83068a0376c6eaca210007744d00c8b4ce53279a67cc069cc519e7\
-80ab89aa446df59ffe2f29cdb917b760d740ceb634c731b93bf1661aa5868b54\
-1e13ab51b3198619cc0016599562ed4d266d1481d0d273d3f97cffe5f8e0dd21\
-5aeb8ed89aafc971a857b8d02f3e3c37ef15ba0e3220e3a7c13c9da8af0c393b\
-518c338b1430e3129c2555650e5d5634d89513f694ba3a5f2aeb444c540f125a\
-aba8c5682695f3feee64772d0e49b432c96470e7d663098e9c271a91d4fc991a\
-0ed800dabe29af5fb41a41cc49fd4084deb02442e8e66f88186607f46395e533\
-a31b642cd5453c7bb16c82bc67bd3b66fa4db58b8e9aa45f9b579860f18d402c\
-798b84002e95753e3b07027a8d68b0a7ab2ac40328fc7ca3ea40780b3428dbc1"
#define hex_fp12_pow	"43291d68970ec9c00ed4616b8fa4b2b332c15a6e4ed833a4b1d68db20a06896c\
-48f861508cb878a1f1f806a486f3aa6889571bd5fb1010d73933550d219afd14\
-34b20766a4cc466efe1ee0d48206d683890494aec331d5b345e9a9adb5c5845a\
-0e3edea737b3db1083b776eb48e7bfaa4256a8d37d7ab13a370d7682daaf794d\
-9808adfd960da7837736fca5acb13a84d56962a21af424e48c0aa52c77dfd157\
-a8aa94ea4f3026eed8fa99ab9a793468db12bb7256c50570e72e375f981861a1\
-3fd308b4cdcec640fa4f17aac455b2f3daed3fb86a850b47c301c3941dbd6c4c\
-11b99f09fa20368e840c3d76e706939e4a3e8367165bb802de43acc83ae622d5\
-a5e97a50168650cae7b02b4c2511eeb194cd5ea5ff02a0284abd5961b46d47e4\
-b52a91d96353ef501bdbe6424ea26414faeeb930b9e618c2882a85d1fdeea3d0\
-6c78632b7dbbbdbf347a3f5fd6935a9f9b425125b7ac106e3586a7fbee3f2f20\
-6b35df1d1153684f1363fce020088a797802e18959df4f006bc5d7f4a632e9f9"

int test_sm9_fp12() {
	sm9_fp12_t x;
	sm9_fp12_t y;
	sm9_fp12_t r;
	sm9_fp12_t s;
	sm9_bn_t k;
	int j = 1;
	
	sm9_fp4_from_hex(x[0], hex_fp4_mul);
	sm9_fp4_from_hex(x[1], hex_fp4_mul_fp);
	sm9_fp4_from_hex(x[2], hex_fp4_mul_fp2);
	sm9_fp4_from_hex(y[0], hex_fp4_mul_v);
	sm9_fp4_from_hex(y[1], hex_fp4_sqr);
	sm9_fp4_from_hex(y[2], hex_fp4_inv);
	sm9_bn_from_hex(k, hex_iv);
	
	sm9_fp12_mul(r, x, y); sm9_fp12_from_hex(s, hex_fp12_mul); if (!sm9_fp12_equ(r, s)) goto err; ++j;
	sm9_fp12_sqr(r, x);    sm9_fp12_from_hex(s, hex_fp12_sqr); if (!sm9_fp12_equ(r, s)) goto err; ++j;
	sm9_fp12_inv(r, x);    sm9_fp12_from_hex(s, hex_fp12_inv); if (!sm9_fp12_equ(r, s)) goto err; ++j;
	sm9_fp12_pow(r, x, k); sm9_fp12_from_hex(s, hex_fp12_pow); if (!sm9_fp12_equ(r, s)) goto err; ++j;
	
	printf("%s() ok\n", __FUNCTION__);
	return 1;
err:
	printf("%s test %d failed\n", __FUNCTION__, j);
	error_print();
	return -1;
}

#define hex_point1	"917be49d159184fba140f4dfc5d653464e94f718fe195b226b3f715829e6e768-288578d9505d462867a50acee40ee143b896e72505be10e8ce4c6b0c945b642b"
#define hex_point2	"593417680f252445fd0522383e23c77a54b11fe222de4a886eabc26e16bffa3c-38e8fc9a8b60f5ba0c6c411f721c117044435a833757d8fee65828511b8b245d"
#define hex_point_dbl	"268def7968f1e8c51635e277425403df88355fb2ecf16f7920f112eb2a7e50c9-5c596b534bbaa85c1d3aecf436e61ff1bfd9f70856f0309c2a63d8248205d84e"
#define hex_point_add	"056610cb69f8d5659ea94e4a67bbf3b93fb0bd449672d7ca2525ec3b68c894d1-88f3f99ce78ed3ffe6ca1cface5242570cb5d053f16a8e0baae10414babd86a7"
#define hex_point_neg	"917be49d159184fba140f4dfc5d653464e94f718fe195b226b3f715829e6e768-8dba8726b24660c96e5ea081117fe601695bac2614bcddf31723301b4ef5e152"
#define hex_point_sub	"29e4a54cad98da9939b95f677784bff3b1dd9334c83d93e351e0f8f7c4ce2dc5-4473eba3b8ff990b8456c41ec0727b76cb2b0f960495b144949f70bf95643b82"
#define hex_point_mul	"997fcff625adbae62566f684f9e89181713f972c5a9cd9ce6764636761ba87d1-8142a28d1bd109501452a649e2d68f012e265460e0c7d3da743fb036eb23b03b"
#define hex_point_mul_g	"7cf689748f3714490d7a19eae0e7bfad0e0182498b7bcd8a6998dfd00f59be51-4e2e98d190e9d775e0caa943196bfb066d9c30818b2d768fb5299e7135830a6f"

int test_sm9_point() {
	sm9_point_t p;
	sm9_point_t q;
	sm9_point_t r;
	sm9_point_t s;
	sm9_bn_t k;
	int j = 1;
	
	sm9_bn_from_hex(k, hex_iv);
	
	sm9_point_from_hex(&p, hex_point1); if (!sm9_point_is_on_curve(&p)) goto err; ++j;
	sm9_point_from_hex(&q, hex_point2); if (!sm9_point_is_on_curve(&q)) goto err; ++j;
	sm9_point_dbl(&r, &p);     sm9_point_from_hex(&s, hex_point_dbl); if (!sm9_point_equ(&r, &s)) goto err; ++j;
	sm9_point_add(&r, &p, &q); sm9_point_from_hex(&s, hex_point_add); if (!sm9_point_equ(&r, &s)) goto err; ++j;
	sm9_point_neg(&r, &p);     sm9_point_from_hex(&s, hex_point_neg); if (!sm9_point_equ(&r, &s)) goto err; ++j;
	sm9_point_sub(&r, &p, &q); sm9_point_from_hex(&s, hex_point_sub); if (!sm9_point_equ(&r, &s)) goto err; ++j;
	sm9_point_mul(&r, k, &p);  sm9_point_from_hex(&s, hex_point_mul); if (!sm9_point_equ(&r, &s)) goto err; ++j;
	sm9_point_mul_generator(&r, k); sm9_point_from_hex(&s, hex_point_mul_g); if (!sm9_point_equ(&r, &s)) goto err; ++j;
	
	printf("%s() ok\n", __FUNCTION__);
	return 1;
err:
	printf("%s test %d failed\n", __FUNCTION__, j);
	error_print();
	return -1;
}

#define hex_tpoint1	"83f6a65d85d51ec72eacf19bc38384e0369eb22a134a725a0191faa6e4f192ef\
-9a79bfd491ef1cb32d9b57f7d0590ccff6b1cfe63dd15c0823d692fafbe96dbc\
-9ed11c499291db0454d738555af0ce8a1df960056ee7425a6bf296eae60a5037\
-849d4434eb7113fc9fb3809b51d54064fa2f20503423d256bc044905b1eba3fb"
#define hex_tpoint2	"a36232a9713f69157b7cdceef54aa0237b3ba0642a80dbb597af8935aea2c130\
-624b19114e49f00281e2aee1f1b9d4f0a081a135868f8bbdb7b7a7b7da5fd6bc\
-77966917ec1c5a294dd836c34691ab5e891f8c9f017443902c0a73ec54d449d8\
-1be45454b6fa085a53744b22fd398238e400c3e031c8796e59e1bd6222048af0"
#define hex_tpoint_neg	"83f6a65d85d51ec72eacf19bc38384e0369eb22a134a725a0191faa6e4f192ef\
-9a79bfd491ef1cb32d9b57f7d0590ccff6b1cfe63dd15c0823d692fafbe96dbc\
-176ee3b67011cbed812c72fa9a9df8bb03f93345ab93ac81797d043cfd46f546\
-31a2bbcb173292f536502ab4a3b986e027c372fae6571c85296b52223165a182"
#define hex_tpoint_dbl	"73cbced58a8e76ef5235b480050a74e906e4d27185bd85d7ebdcd43ad24475fd\
-58400f0eb23000d814f5b5d0706749a72909795b7b04f26d6d58b2cf478ad9c9\
-19b460e09ac9ddbb380d6441e078a47bfcaa7d4c3d60b3a6c0d05f896472dc3c\
-1d69f785f47d6f25cb901b131612c37edc5e89ee9ba2dac8c401ced40e340a39"
#define hex_tpoint_add	"5f443752a19e368f404b89abae20a386d2b534c424b93ededdbfd04d4c569e6b\
-a411bbd84ee92a6ee53e5ca9cb81bacc192c6ba406f6fdcb2b04d0ab9c42ae44\
-6a3dadfcaac134e8353dd3abf37d487b206ca28dfab1e0a9376649df748f1605\
-4fa25e5e6100a023d4923df385dd236749c6a7f8e68db55e0bd1e2263fc04d28"
#define hex_tpoint_sub	"3cbbf5fcc6c11a3579036e617bbf0b2861c53979f01e37f59fc4a10d991ccde7\
-1e9c3c99524c7867c9dbc4f52fdc938cf5aa4a980d3905cc91a5b91331235290\
-44027c5d814bab73ad93d14b564303aab153ad7355bcfbf8a8bed7cb577e7fd8\
-47a4037d1d6f6d2014aa04292fa91cf07b1f4331a85d4b66a6e048226ddfc43e"
#define hex_tpoint_mul	"5d704de3261290dbba39dbd14e6bc416025240fd1ed65ec982efed685ae41e8b\
-705c9ca4b5ef465c4e5db80ca4880627a6d9d6bcefd4756496baba9d5eaa3304\
-4e96eb3543aabf1e9a65cae24177b9d13b0f7fae9472145ba7ae2b14bb447aef\
-5d7ba50d7eac49a00b18fee2069afd3cc9719993fa78271e66b7a3efed46ac8b"
#define hex_tpoint_mulg "920ef6fb3a2acff52aa0c004c18feca149dfd33d98086f8f402ea9e0de303c49\
-1f97dd359f2b065d63e0987f5bea2f3dc865c2cc112d7d161b46b83451716fd8\
-614881d4d05fef3173a4990465876c5200f58c5015e13354b23ae401c20c4aef\
-18a22e02b7d395a49f0646a79438e79cd37c32f163fe8923c13d56bab668e8a7"

int test_sm9_twist_point() {
	sm9_twist_point_t p;
	sm9_twist_point_t q;
	sm9_twist_point_t r;
	sm9_twist_point_t s;
	sm9_bn_t k;
	int j = 1;
	
	sm9_bn_from_hex(k, hex_iv);
	
	sm9_twist_point_from_hex(&p, hex_tpoint1); if (!sm9_twist_point_is_on_curve(&p)) goto err; ++j;
	sm9_twist_point_from_hex(&q, hex_tpoint2); if (!sm9_twist_point_is_on_curve(&q)) goto err; ++j;
	sm9_twist_point_neg(&r, &p);     sm9_twist_point_from_hex(&s, hex_tpoint_neg); if (!sm9_twist_point_equ(&r, &s)) goto err; ++j;
	sm9_twist_point_dbl(&r, &p);     sm9_twist_point_from_hex(&s, hex_tpoint_dbl); if (!sm9_twist_point_equ(&r, &s)) goto err; ++j;
	sm9_twist_point_add(&r, &p, &q); sm9_twist_point_from_hex(&s, hex_tpoint_add); if (!sm9_twist_point_equ(&r, &s)) goto err; ++j;
	sm9_twist_point_add_full(&r, &p, &q); if (!sm9_twist_point_equ(&r, &s)) goto err; ++j;
	sm9_twist_point_sub(&r, &p, &q); sm9_twist_point_from_hex(&s, hex_tpoint_sub); if (!sm9_twist_point_equ(&r, &s)) goto err; ++j;
	sm9_twist_point_mul(&r, k, &p);  sm9_twist_point_from_hex(&s, hex_tpoint_mul); if (!sm9_twist_point_equ(&r, &s)) goto err; ++j;
	sm9_twist_point_mul_generator(&r, k);    sm9_twist_point_from_hex(&s, hex_tpoint_mulg); if (!sm9_twist_point_equ(&r, &s)) goto err; ++j;
	
	printf("%s() ok\n", __FUNCTION__);
	return 1;
err:
	printf("%s test %d failed\n", __FUNCTION__, j);
	error_print();
	return -1;
}

#define hex_pairing1	"4e378fb5561cd0668f906b731ac58fee25738edf09cadc7a29c0abc0177aea6d\
-28b3404a61908f5d6198815c99af1990c8af38655930058c28c21bb539ce0000\
-38bffe40a22d529a0c66124b2c308dac9229912656f62b4facfced408e02380f\
-a01f2c8bee81769609462c69c96aa923fd863e209d3ce26dd889b55e2e3873db\
-67e0e0c2eed7a6993dce28fe9aa2ef56834307860839677f96685f2b44d0911f\
-5a1ae172102efd95df7338dbc577c66d8d6c15e0a0158c7507228efb078f42a6\
-1604a3fcfa9783e667ce9fcb1062c2a5c6685c316dda62de0548baa6ba30038b\
-93634f44fa13af76169f3cc8fbea880adaff8475d5fd28a75deb83c44362b439\
-b3129a75d31d17194675a1bc56947920898fbf390a5bf5d931ce6cbb3340f66d\
-4c744e69c4a2e1c8ed72f796d151a17ce2325b943260fc460b9f73cb57c9014b\
-84b87422330d7936eaba1109fa5a7a7181ee16f2438b0aeb2f38fd5f7554e57a\
-aab9f06a4eeba4323a7833db202e4e35639d93fa3305af73f0f071d7d284fcfb"

#define hex_RA	"7CBA5B19069EE66AA79D490413D11846B9BA76DD22567F809CF23B6D964BB265-A9760C99CB6F706343FED05637085864958D6C90902ABA7D405FBEDF7B781599"
#define hex_deB	"74CCC3AC9C383C60AF083972B96D05C75F12C8907D128A17ADAFBAB8C5A4ACF7\
-01092FF4DE89362670C21711B6DBE52DCD5F8E40C6654B3DECE573C2AB3D29B2\
-44B0294AA04290E1524FF3E3DA8CFD432BB64DE3A8040B5B88D1B5FC86A4EBC1\
-8CFC48FB4FF37F1E27727464F3C34E2153861AD08E972D1625FC1A7BD18D5539"
#define hex_pairing2	"28542FB6954C84BE6A5F2988A31CB6817BA0781966FA83D9673A9577D3C0C134\
-5E27C19FC02ED9AE37F5BB7BE9C03C2B87DE027539CCF03E6B7D36DE4AB45CD1\
-A1ABFCD30C57DB0F1A838E3A8F2BF823479C978BD137230506EA6249C891049E\
-3497477913AB89F5E2960F382B1B5C8EE09DE0FA498BA95C4409D630D343DA40\
-4FEC93472DA33A4DB6599095C0CF895E3A7B993EE5E4EBE3B9AB7D7D5FF2A3D1\
-647BA154C3E8E185DFC33657C1F128D480F3F7E3F16801208029E19434C733BB\
-73F21693C66FC23724DB26380C526223C705DAF6BA18B763A68623C86A632B05\
-0F63A071A6D62EA45B59A1942DFF5335D1A232C9C5664FAD5D6AF54C11418B0D\
-8C8E9D8D905780D50E779067F2C4B1C8F83A8B59D735BB52AF35F56730BDE5AC\
-861CCD9978617267CE4AD9789F77739E62F2E57B48C2FF26D2E90A79A1D86B93\
-9B1CA08F64712E33AEDA3F44BD6CB633E0F722211E344D73EC9BBEBC92142765\
-6BA584CE742A2A3AB41C15D3EF94EDEB8EF74A2BDCDAAECC09ABA567981F6437"

#define hex_Ppube	"9174542668E8F14AB273C0945C3690C66E5DD09678B86F734C4350567ED06283-54E598C6BF749A3DACC9FFFEDD9DB6866C50457CFC7AA2A4AD65C3168FF74210"
#define rB		"00018B98C44BEF9F8537FB7D071B2C928B3BC65BD3D69E1EEE213564905634FE"
#define hex_pairing3	"1052D6E9D13E381909DFF7B2B41E13C987D0A9068423B769480DACCE6A06F492\
-5FFEB92AD870F97DC0893114DA22A44DBC9E7A8B6CA31A0CF0467265A1FB48C7\
-2C5C3B37E4F2FF83DB33D98C0317BCBBBBF4AC6DF6B89ECA58268B280045E612\
-6CED9E2D7C9CD3D5AD630DEFAB0B831506218037EE0F861CF9B43C78434AEC38\
-0AE7BF3E1AEC0CB67A03440906C7DFB3BCD4B6EEEBB7E371F0094AD4A816088D\
-98DBC791D0671CACA12236CDF8F39E15AEB96FAEB39606D5B04AC581746A663D\
-00DD2B7416BAA91172E89D5309D834F78C1E31B4483BB97185931BAD7BE1B9B5\
-7EBAC0349F8544469E60C32F6075FB0468A68147FF013537DF792FFCE024F857\
-10CC2B561A62B62DA36AEFD60850714F49170FD94A0010C6D4B651B64F3A3A5E\
-58C9687BEDDCD9E4FEDAB16B884D1FE6DFA117B2AB821F74E0BF7ACDA2269859\
-2A430968F16086061904CE201847934B11CA0F9E9528F5A9D0CE8F015C9AEA79\
-934FDDA6D3AB48C8571CE2354B79742AA498CB8CDDE6BD1FA5946345A1A652F6"

int test_sm9_pairing() {
	sm9_twist_point_t p;
	sm9_point_t q;
	sm9_fp12_t r;
	sm9_fp12_t s;
	sm9_bn_t k;
	int j = 1;
	
	sm9_pairing(r, SM9_Ppubs, SM9_P1); sm9_fp12_from_hex(s, hex_pairing1); if (!sm9_fp12_equ(r, s)) goto err; ++j;
	
	sm9_twist_point_from_hex(&p, hex_deB); sm9_point_from_hex(&q, hex_RA);
	sm9_pairing(r, &p, &q); sm9_fp12_from_hex(s, hex_pairing2); if (!sm9_fp12_equ(r, s)) goto err; ++j;
	
	sm9_bn_from_hex(k, rB); sm9_point_from_hex(&q, hex_Ppube);
	sm9_pairing(r, SM9_P2, &q); sm9_fp12_pow(r, r, k); sm9_fp12_from_hex(s, hex_pairing3); if (!sm9_fp12_equ(r, s)) goto err; ++j;
	
	printf("%s() ok\n", __FUNCTION__);
	return 1;
err:
	printf("%s test %d failed\n", __FUNCTION__, j);
	error_print();
	return -1;
}

int main(void) {
	if (test_sm9_fp() != 1) goto err;
	if (test_sm9_fp2() != 1) goto err;
	if (test_sm9_fp4() != 1) goto err;
	if (test_sm9_fp12() != 1) goto err;
	if (test_sm9_point() != 1) goto err;
	if (test_sm9_twist_point() != 1) goto err;
	if (test_sm9_pairing() != 1) goto err;

	printf("%s all tests passed\n", __FILE__);
	return 0;
err:
	error_print();
	return -1;
}
