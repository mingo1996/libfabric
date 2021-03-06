/*
 * (C) Copyright 2020 Hewlett Packard Enterprise Development LP
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _OFI_HMEM_H_
#define _OFI_HMEM_H_

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <rdma/fi_domain.h>

#ifdef HAVE_LIBCUDA

#include <cuda.h>
#include <cuda_runtime.h>

/* Libfabric supported CUDA operations. */
cudaError_t ofi_cudaMemcpy(void* dst, const void* src, size_t count,
			   enum cudaMemcpyKind kind);
const char *ofi_cudaGetErrorName(cudaError_t error);
const char *ofi_cudaGetErrorString(cudaError_t error);
CUresult ofi_cuPointerGetAttribute(void *data, CUpointer_attribute attribute,
				   CUdeviceptr ptr);

#endif /* HAVE_LIBCUDA */

int cuda_copy_to_dev(void *dev, const void *host, size_t size);
int cuda_copy_from_dev(void *host, const void *dev, size_t size);
int cuda_hmem_init(void);
int cuda_hmem_cleanup(void);

static inline int ofi_memcpy(void *dest, const void *src, size_t size)
{
	memcpy(dest, src, size);
	return FI_SUCCESS;
}

static inline int ofi_hmem_init_noop(void)
{
	return FI_SUCCESS;
}

static inline int ofi_hmem_cleanup_noop(void)
{
	return FI_SUCCESS;
}

ssize_t ofi_copy_from_hmem_iov(void *dest, size_t size,
			       const struct iovec *hmem_iov,
			       enum fi_hmem_iface hmem_iface,
			       size_t hmem_iov_count, uint64_t hmem_iov_offset);

ssize_t ofi_copy_to_hmem_iov(const struct iovec *hmem_iov,
			     enum fi_hmem_iface hmem_iface,
			     size_t hmem_iov_count, uint64_t hmem_iov_offset,
			     void *src, size_t size);

void ofi_hmem_init(void);
void ofi_hmem_cleanup(void);

#endif /* _OFI_HMEM_H_ */
