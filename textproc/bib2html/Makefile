PORTNAME=	bib2html
DISTVERSION=	6.7
CATEGORIES=	textproc print
MASTER_SITES=	TEX/biblio/bibtex/utils
DISTNAME=	bib2ml
DIST_SUBDIR=	${PORTNAME}/${PORTVERSION}

MAINTAINER=	ports@FreeBSD.org
COMMENT=	BibTeX to HTML Translator
WWW=		https://www.arakhne.org/

LICENSE=	GPLv2+
LICENSE_FILE=	${WRKSRC}/../COPYING

WRKSRC_SUBDIR=	src

USES=		perl5 shebangfix zip
SHEBANG_FILES=	*.pl
USE_PERL5=	run
NO_BUILD=	yes
NO_ARCH=	yes

CONFLICTS_INSTALL=	bibutils sowing # bin/bib2html bin/bib2xml

post-patch:
.for i in bib2html bib2sql bib2xml
	@${SED} -e \
		's:= "$$0";:= "${SITE_PERL}/Bib2HTML";:g' \
		< ${WRKSRC}/${i}.pl > ${WRKSRC}/${i}
.endfor

do-install:
	(cd ${WRKSRC} && ${INSTALL_SCRIPT} bib2html bib2sql bib2xml \
		${STAGEDIR}${PREFIX}/bin)
	${MKDIR} ${STAGEDIR}${PREFIX}/${SITE_PERL_REL}/Bib2HTML
	(cd ${WRKSRC}/Bib2HTML && ${COPYTREE_SHARE} . ${STAGEDIR}${PREFIX}/${SITE_PERL_REL}/Bib2HTML)

.include <bsd.port.mk>
