PORTNAME=	pastedeploy
PORTVERSION=	3.0.1
PORTREVISION=	1
CATEGORIES=	www python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
DISTNAME=	PasteDeploy-${PORTVERSION}

MAINTAINER=	sunpoet@FreeBSD.org
COMMENT=	Load, configure, and compose WSGI applications and servers
WWW=		https://pylonsproject.org/ \
		https://github.com/Pylons/pastedeploy

LICENSE=	MIT

BUILD_DEPENDS=	${PY_SETUPTOOLS} \
		${PYTHON_PKGNAMEPREFIX}wheel>=0:devel/py-wheel@${PY_FLAVOR}

USES=		python
USE_PYTHON=	autoplist concurrent pep517

NO_ARCH=	yes

.include <bsd.port.mk>
