PORTNAME=		libgeodecomp
PORTVERSION=		0.4.0
PORTREVISION=		24
CATEGORIES=		science devel
MASTER_SITES=		http://www.libgeodecomp.org/archive/

MAINTAINER=		kurt@kmk-computers.de
COMMENT=		Auto-parallelizing library for computer simulations
WWW=		http://www.libgeodecomp.org/

LICENSE=		BSL
LICENSE_FILE=		${WRKSRC}/LICENSE

LIB_DEPENDS=		libboost_system.so:devel/boost-libs libboost_date_time.so:devel/boost-libs \
			libboost_filesystem.so:devel/boost-libs

BROKEN=			error: incomplete type 'LibFlatArray::detail::flat_array::offset<LibGeoDecomp::TestCell<3, LibGeoDecomp::Stencils::Moore<3, 1>, LibGeoDecomp::TopologiesHelpers::Topology<3, false, false, false>, LibGeoDecomp::TestCellHelpers::SoAAPI>, -1>' used in nested name specifier

USES=			cmake compiler:c++11-lib
USE_GCC=		yes
USE_LDCONFIG=		yes

CMAKE_ARGS=		-DWITH_CUDA:BOOL=FALSE -DWITH_VISIT:BOOL=FALSE \
			-DWITH_HPX:BOOL=FALSE -DWITH_OPENCL:BOOL=FALSE \
			-DWITH_OPENCV:BOOL=FALSE -DWITH_TYPEMAPS=FALSE

OPTIONS_DEFINE=		MPI SILO SCOTCH
OPTIONS_DEFAULT=	MPI SILO SCOTCH

MPI_LIB_DEPENDS=	libmpich.so:net/mpich
MPI_CMAKE_BOOL=		WITH_MPI

SILO_DESC=		Enable Silo dependend output
SILO_LIB_DEPENDS=	libsiloh5.so:science/silo
SILO_CMAKE_BOOL=	WITH_SILO

SCOTCH_DESC=		Enable graph partitioning based on Scotch/Scotch-PT
SCOTCH_LIB_DEPENDS=	libscotch.so:cad/scotch
SCOTCH_CMAKE_BOOL=	WITH_SCOTCH

.include <bsd.port.mk>
