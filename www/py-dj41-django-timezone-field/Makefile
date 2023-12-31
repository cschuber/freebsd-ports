PORTNAME=	django-timezone-field
DISTVERSION=	5.1
CATEGORIES=	www python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}dj41-
DISTNAME=	django_timezone_field-${DISTVERSION}

MAINTAINER=	kai@FreeBSD.org
COMMENT=	Provides database and form fields for pytz timezone objects for Django
WWW=		https://github.com/mfogel/django-timezone-field

LICENSE=	BSD2CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

DEPRECATED=	Extended support of Django 4.1 ends December 2023, upgrade to the Django 4.2+ version of this port. See https://www.djangoproject.com/download/
EXPIRATION_DATE=	2023-12-31

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}poetry-core>=1.0.0:devel/py-poetry-core@${PY_FLAVOR}
RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}django41>=2.2:www/py-django41@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pytz>0:devel/py-pytz@${PY_FLAVOR}

USES=		python
USE_PYTHON=	autoplist pep517

CONFLICTS_INSTALL=	${PYTHON_PKGNAMEPREFIX}*${PORTNAME}

NO_ARCH=		yes

.include <bsd.port.pre.mk>

.if ${PYTHON_REL} < 30900
RUN_DEPENDS+=	${PYTHON_PKGNAMEPREFIX}backports.zoneinfo>=0.2.1<0.3.0:devel/py-backports.zoneinfo@${PY_FLAVOR}
.endif

.include <bsd.port.post.mk>
