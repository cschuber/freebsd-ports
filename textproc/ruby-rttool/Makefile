PORTNAME=	rttool
PORTVERSION=	1.0.3
PORTREVISION=	1
CATEGORIES=	textproc ruby
MASTER_SITES=	http://www.rubyist.net/~rubikitch/archive/ \
		LOCAL/tota/ruby-rttool
PKGNAMEPREFIX=	${RUBY_PKGNAMEPREFIX}
DIST_SUBDIR=	${RUBY_PKGNAMEPREFIX:S|${RUBY_SUFFIX}-||}

MAINTAINER=	tota@FreeBSD.org
COMMENT=	RT into HTML and plain text converter
WWW=		http://www.rubyist.net/~rubikitch/computer/rttool/index.en.html

LICENSE=	RUBY

USES=		ruby:setup shebangfix

SHEBANG_FILES=	bin/rt/* lib/rt/*
RUBY_MODNAME=	rt

BUILD_DEPENDS=	rd2:textproc/ruby-rdtool

DOCS_EN=	rttool.en.html rttool.en.rd
DOCS_JA=	rttool.ja.html rttool.ja.rd

OPTIONS_DEFINE=	DOCS EXAMPLES

post-install:
	@${MKDIR} ${STAGEDIR}${RUBY_MODDOCDIR}/ja
.for f in ${DOCS_EN}
	${INSTALL_DATA} ${WRKSRC}/${f} ${STAGEDIR}${RUBY_MODDOCDIR}/
.endfor
.for f in ${DOCS_JA}
	${INSTALL_DATA} ${WRKSRC}/${f} ${STAGEDIR}${RUBY_MODDOCDIR}/ja/
.endfor
	@${MKDIR} ${STAGEDIR}${RUBY_MODEXAMPLESDIR}
	cd ${WRKSRC}/examples && ${COPYTREE_SHARE} . ${STAGEDIR}${RUBY_MODEXAMPLESDIR}

.include <bsd.port.mk>
