from setuptools import setup, find_packages


def main():
    setup(
        name='BFGP',
        version='0.3',
        author="Javier Segovia-Aguas",
        packages=find_packages('preprocess'),
        package_dir={'': 'preprocess'},
        setup_requires=['wheel'],
    )


if __name__ == "__main__":
    main()
