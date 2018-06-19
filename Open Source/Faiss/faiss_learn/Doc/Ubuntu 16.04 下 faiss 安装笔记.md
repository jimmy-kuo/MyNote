## 前言 faiss 简介

三月初，Facebook AI Research（FAIR）开源了一个名为 Faiss 的库，Faiss 主要用于有效的相似性搜索（Similarity Search）和稠密矢量聚类（Clustering of dense vectors），包含了在任何大小的矢量集合里进行搜索的算法。Faiss 上矢量集合的大小甚至可以大到装不进 RAM。这个库基本上是用 C++ 实现的，带有可选的通过 CUDA 提供的 GPU 支持，以及一个可选的 Python 接口。

通过 Faiss 进行相似性搜索时，10 亿图像数据库上的一次查询仅耗时 17.7 微秒，速度较之前提升了 8.5 倍，且准确度也有所提升。

Github : https://github.com/facebookresearch/faiss
Wiki : https://github.com/facebookresearch/faiss/wiki

参照官方的 [INSTALL.md]() 开始安装过程.

## 安装 Conda
> 安装FAISS最简单的方法是通过anaconda。我们经常将稳定版本推送到conda

1. Conda 是什么
conda 是一个 Python科学计算环境. Anaconda是 Python 的科学计算工具包。根据对 Python2 和 Python3 的支持，分为 Anaconda2 和 Anaconda3。官网提供的是最新的版本

2. 下载并安装Conda
根据 [官方安装文档](https://conda.io/docs/user-guide/install/linux.html),首先下载 **Anaconda** ,之后通过以下命令开始安装,并根据屏幕上的提示确认安装设置. 稍等一会即可安装完成. 
* 特别注意,在安装完相关计算环境之后,会提示你是否将anaconda安装路径加入到环境变量. 请输入 `yes`

 ```shell
$ bash Anaconda{你下载的版本}x86_64.sh

Welcome to Anaconda2 5.2.0

In order to continue the installation process, please review the license
agreement.
Please, press ENTER to continue
>>> 
===================================
Anaconda End User License Agreement
===================================

Copyright 2015, Anaconda, Inc.

All rights reserved under the 3-clause BSD License:

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
  * Neither the name of Anaconda, Inc. ("Anaconda, Inc.") nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PAR
TICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL ANACONDA, INC. BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBS
TITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWI
SE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Notice of Third Party Software Licenses
=======================================

Anaconda Distribution contains open source software packages from third parties. These are available on an "as is" basis and subject to their individual license agreements. These licenses are available in Anac
onda Distribution or at http://docs.anaconda.com/anaconda/pkg-docs. Any binary packages of these third party tools you obtain via Anaconda Distribution are subject to their individual licenses as well as the A
naconda license. Anaconda, Inc. reserves the right to change which third party tools are provided in Anaconda Distribution.

In particular, Anaconda Distribution contains re-distributable, run-time, shared-library files from the Intel(TM) Math Kernel Library ("MKL binaries"). You are specifically authorized to use the MKL binaries w
ith your installation of Anaconda Distribution. You are also authorized to redistribute the MKL binaries with Anaconda Distribution or in the conda package that contains them. Use and redistribution of the MKL
 binaries are subject to the licensing terms located at https://software.intel.com/en-us/license/intel-simplified-software-license. If needed, instructions for removing the MKL binaries after installation of A
naconda Distribution are available at http://www.anaconda.com.

Anaconda Distribution also contains cuDNN software binaries from NVIDIA Corporation ("cuDNN binaries"). You are specifically authorized to use the cuDNN binaries with your installation of Anaconda Distribution
. You are also authorized to redistribute the cuDNN binaries with an Anaconda Distribution package that contains them. If needed, instructions for removing the cuDNN binaries after installation of Anaconda Dis
tribution are available at http://www.anaconda.com.


Anaconda Distribution also contains Visual Studio Code software binaries from Microsoft Corporation ("VS Code"). You are specifically authorized to use VS Code with your installation of Anaconda Distribution. 
Use of VS Code is subject to the licensing terms located at https://code.visualstudio.com/License.

Cryptography Notice
===================

This distribution includes cryptographic software. The country in which you currently reside may have restrictions on the import, possession, use, and/or re-export to another country, of encryption software. B
EFORE using any encryption software, please check your country's laws, regulations and policies concerning the import, possession, or use, and re-export of encryption software, to see if this is permitted. See
 the Wassenaar Arrangement http://www.wassenaar.org/ for more information.

Anaconda, Inc. has self-classified this software as Export Commodity Control Number (ECCN) 5D992b, which includes mass market information security software using or performing cryptographic functions with asym
metric algorithms. No license is required for export of this software to non-embargoed countries. In addition, the Intel(TM) Math Kernel Library contained in Anaconda, Inc.'s software is classified by Intel(TM
) as ECCN 5D992b with no license required for export to non-embargoed countries and Microsoft's Visual Studio Code software is classified by Microsoft as ECCN 5D992.c with no license required for export to non
-embargoed countries.

The following packages are included in this distribution that relate to cryptography:

openssl
    The OpenSSL Project is a collaborative effort to develop a robust, commercial-grade, full-featured, and Open Source toolkit implementing the Transport Layer Security (TLS) and Secure Sockets Layer (SSL) pr
otocols as well as a full-strength general purpose cryptography library.

pycrypto
    A collection of both secure hash functions (such as SHA256 and RIPEMD160), and various encryption algorithms (AES, DES, RSA, ElGamal, etc.).

pyopenssl
    A thin Python wrapper around (a subset of) the OpenSSL library.

kerberos (krb5, non-Windows platforms)
    A network authentication protocol designed to provide strong authentication for client/server applications by using secret-key cryptography.

cryptography
    A Python library which exposes cryptographic recipes and primitives.


Do you accept the license terms? [yes|no]
[no] >>> 
Please answer 'yes' or 'no':'
>>> yes

Anaconda2 will now be installed into this location:
/root/anaconda2

  - Press ENTER to confirm the location
  - Press CTRL-C to abort the installation
  - Or specify a different location below

[/root/anaconda2] >>> 
PREFIX=/root/anaconda2
installing: python-2.7.15-h1571d57_0 ...
Python 2.7.15 :: Anaconda, Inc.
installing: blas-1.0-mkl ...

...

installation finished.
Do you wish the installer to prepend the Anaconda2 install location
to PATH in your /root/.bashrc ? [yes|no]
[no] >>> yes

Appending source /root/anaconda2/bin/activate to /root/.bashrc
A backup will be made to: /root/.bashrc-anaconda2.bak


For this change to become active, you have to open a new terminal.

Thank you for installing Anaconda2!

===========================================================================

Anaconda is partnered with Microsoft! Microsoft VSCode is a streamlined
code editor with support for development operations like debugging, task
running and version control.

To install Visual Studio Code, you will need:
  - Administrator Privileges
  - Internet connectivity

Visual Studio Code License: https://code.visualstudio.com/license

Do you wish to proceed with the installation of Microsoft VSCode? [yes|no]
>>> no
$
```
如果没输入就要配置环境，根据提示，在终端输入
```
sudo vim /etc/profile
```
打开profile文件。在最后添加语句`export PATH={你的Anaconda2安装路径}/bin:$PATH`，保存，退出。
最后```source /etc/profile```使配置生效.

3. 测试Conda是否安装成功
在终端中输入
```shell
conda list
```
若发现输出了conda所安装的库列表,则代表Conda安装成功.

再试一下 在Python中
```
Python 2.7.15 |Anaconda, Inc.| (default, May  1 2018, 23:32:55) 
[GCC 7.2.0] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> import scipy
>>> 
```
开头提示信息出现Anaconda字样,且import无报错, 则Anaconda安装过程完成.

## 安装 OpenBLAS
BLAS即是Basic linear Algebra Subprograms，基本线性代数子程序，主要包括矩阵和矩阵，矩阵和向量，向量和向量操作，是科学和工程计算的基础数学库之一。

OpenBLAS的开源项目源于GotoBLAS项目，大致从2011年开始，当前的稳定版本是0.2.14，主要开发人员才三个，贡献者多达44人；已经进入主流Linux发行版的源，并且成为MIT以及其他如GNU，DL等的主要依赖库。

1. 通过 conda 安装 openblas
```shell
conda install openblas
```

2. 创建软连接
```shell
ln -s $HOME/anaconda2/lib/libopenblas.so.0 /usr/lib64/libopenblas.so.0
```

## 安装 faiss
*源码编译安装方式可以参考 [官方文档](https://github.com/facebookresearch/faiss/blob/master/INSTALL.md#compile-from-source)*

1. 通过Conda安装 faiss
我这里只安装了CPU版本,gpu版本需要先提前安装CUDA. 参考下面的安装命令安装即可
```
# CPU 版本 
# CPU version only
conda install faiss-cpu -c pytorch

# GPU 版本
# Make sure you have CUDA installed before installing faiss-gpu, 
# otherwise it falls back to CPU version
conda install faiss-gpu -c pytorch # [DEFAULT]For CUDA8.0, comes with cudatoolkit8.0
conda install faiss-gpu cuda90 -c pytorch # For CUDA9.0
conda install faiss-gpu cuda91 -c pytorch # For CUDA9.1
# cuda90/cuda91 shown above is a feature, it doesn't install CUDA for you.
```
2. 测试 faiss
在终端中打开Python解释器,尝试 import faiss, 无报错则安装完成.
```python
$ python
Python 2.7.15 |Anaconda, Inc.| (default, May  1 2018, 23:32:55) 
[GCC 7.2.0] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> import faiss
>>> 
```

3. 运行Demo
[官方Python Demo](https://github.com/facebookresearch/faiss/blob/master/tutorial/python/1-Flat.py)
```python
# Copyright (c) 2015-present, Facebook, Inc.
# All rights reserved.
#
# This source code is licensed under the BSD+Patents license found in the
# LICENSE file in the root directory of this source tree.

import numpy as np

d = 64                           # dimension
nb = 100000                      # database size
nq = 10000                       # nb of queries
np.random.seed(1234)             # make reproducible
xb = np.random.random((nb, d)).astype('float32')
xb[:, 0] += np.arange(nb) / 1000.
xq = np.random.random((nq, d)).astype('float32')
xq[:, 0] += np.arange(nq) / 1000.

import faiss                   # make faiss available
index = faiss.IndexFlatL2(d)   # build the index
print(index.is_trained)
index.add(xb)                  # add vectors to the index
print(index.ntotal)

k = 4                          # we want to see 4 nearest neighbors
D, I = index.search(xb[:5], k) # sanity check
print(I)
print(D)
D, I = index.search(xq, k)     # actual search
print(I[:5])                   # neighbors of the 5 first queries
print(I[-5:])                  # neighbors of the 5 last queries
```

## 参考文献

[Linux下安装anaconda](https://blog.csdn.net/xiaerwoailuo/article/details/70054429)

