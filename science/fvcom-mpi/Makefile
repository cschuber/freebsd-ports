PORTREVISION=	16
PKGNAMESUFFIX=	-openmpi

MPIPREFIX=	mpi/openmpi/

LIB_DEPENDS+=	libmpi.so:net/openmpi

MASTERDIR=	${.CURDIR}/../fvcom

MAKE_ARGS+=	FC=${LOCALBASE}/${MPIPREFIX}bin/mpif90 \
		PORT_CPP_FLAGS+=-DMULTIPROCESSOR

.include "${MASTERDIR}/Makefile"
