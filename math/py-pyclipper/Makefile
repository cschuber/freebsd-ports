PORTNAME=	pyclipper
PORTVERSION=	1.2.1
CATEGORIES=	math python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	lantw44@gmail.com
COMMENT=	Cython wrapper for the C++ translation of Clipper library
WWW=		https://github.com/greginvm/pyclipper

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}setuptools_scm>=1.11.1:devel/py-setuptools_scm@${PY_FLAVOR}

USES=		python zip
USE_PYTHON=	distutils cython autoplist

.include <bsd.port.mk>
