PORTNAME=	SoapySDR
DISTVERSIONPREFIX=	soapy-sdr-
DISTVERSION=	0.8.1
CATEGORIES=	misc hamradio python
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	Vendor and platform neutral SDR support library (python binding)
WWW=		https://github.com/pothosware/SoapySDR

LICENSE=	BSL
LICENSE_FILE=	${WRKSRC}/../LICENSE_1_0.txt

BUILD_DEPENDS=	swig:devel/swig
LIB_DEPENDS=	libSoapySDR.so:misc/soapysdr

USES=		cmake compiler:c++11-lang gettext-runtime python
USE_GITHUB=	yes
GH_ACCOUNT=	pothosware
USE_PYTHON=	flavors

CMAKE_ARGS=	-DPYTHON_EXECUTABLE:STRING=${PYTHON_CMD}

WRKSRC_SUBDIR=	python

PLIST_FILES=	${PYTHON_SITELIBDIR}/SoapySDR.py \
		${PYTHON_SITELIBDIR}/_SoapySDR.so

.include <bsd.port.mk>
